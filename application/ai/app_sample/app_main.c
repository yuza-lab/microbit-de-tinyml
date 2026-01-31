/**
 * @file    app_main.c
 * @brief   [I2C経由の加速度センサーの動作確認(μT-Kernel 3.0用)]の改変実装～TinyML姿勢判定実行
 * Project: micro:bit de TinyML♪
 * @author  T3 WG of TRON Forum (Original Author)
 * @author  Modified by ゆざ (@yuza-lab)
 * @version v0.93.0
 * @date    2025-04-05 (Modified)
 * @details
 * 【ライセンスに関する注意 / License Notice】
 * - 本ファイルは「TRONWARE VOL.207」 (パーソナルメディア刊) 掲載の記事コードをベースに改変したものです．
 * - 本ファイルの改変部分 (Modified by ゆざ) については，Apache License, Version 2.0 を適用します．
 * - パーソナルメディア株式会社 出版部よりソースコードの改変ならびに一般公開について許諾を得ております．
 * - オリジナル部分のライセンスについては，原典の規定に従います．
 * 【改変内容 / Modification Details】
 * - 加速度センサデータに基づくボード姿勢推論…TinyML(NNabla C Runtime)使用
 */

/* ======================================================================
 * Modification by ゆざ (@yuza-lab)
 * Copyright 2025 ゆざ (@yuza-lab)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ====================================================================== */

/* Original Copyright Notice */
/*---------------------------------------------------------------
 *	I2C経由の加速度センサーの動作確認(μT-Kernel 3.0用)
 *
 *	Copyright (C) 2022-2024 by T3 WG of TRON Forum
 *---------------------------------------------------------------*/
#include <tk/tkernel.h>
#include <tm/tmonitor.h>

#include "iic.h"			// I2C関連ファイルのインクルード(※A)

#include "pltm_fmath.h"		// [@yuza-lab] 浮動小数点演算代替関数群

#include <nnablart/runtime.h>		// [@yuza-lab] NNabla C Runtime
#include "MainRuntime_inference.h"	// [@yuza-lab] NNabla: Neural Network Model
#include "MainRuntime_parameters.h"	// [@yuza-lab] NNabla: Neural Network Model

//-------- LSM303AGRのI2Cアドレス -------------------------------
#define	IICADR_ACC	0x19	// 加速度センサー
#define	IICADR_MAG	0x1e	// 地磁気センサー

//-------- LSM303AGRの加速度センサーのレジスタアドレス ----------
#define	WHO_AM_I_A	0x0F	// デバイス識別(Who am I)		
#define	CTRL_REG1_A	0x20	// 加速度センサー制御_1		
#define	OUT_X_L_A	0x28	// 加速度センサー出力_X軸下位バイト
#define	OUT_X_H_A	0x29	// 加速度センサー出力_X軸上位バイト
#define	OUT_Y_L_A	0x2A	// 加速度センサー出力_Y軸下位バイト
#define	OUT_Y_H_A	0x2B	// 加速度センサー出力_Y軸上位バイト
#define	OUT_Z_L_A	0x2C	// 加速度センサー出力_Z軸下位バイト
#define	OUT_Z_H_A	0x2D	// 加速度センサー出力_Z軸上位バイト

//-------- iic_reg.cで定義された関数のインポート ----------------
IMPORT INT read_reg( INT adr, INT reg );
IMPORT ER write_reg( INT adr, INT reg, UB dat );
IMPORT ER read_reg_6( INT adr, INT reg, UB dat[6] );

//---------------------------------------------------------------
LOCAL INT get_acc10bit(UB L_dat, UB H_dat){	// 加速度データの後処理(※G)

	H	dat16bit, ret_dat;					// 符号付き16ビット整数(※K)
	
	// 上位8ビットと下位8ビットを16ビットデータにまとめる(※H)
	dat16bit = (H_dat << 8) | L_dat ;

	// 左詰めだった10ビットの符号付きデータを右に6ビットシフト(※J)
	ret_dat = dat16bit >> 6;

	return(ret_dat);
}

//---------------------------------------------------------------
EXPORT void usermain( void )
{
	INT	dat, x_acc, y_acc, z_acc;
	UB	outreg[6];
	ER	err;

	// [@yuza-lab] nnablart: malloc ==> Kmalloc, free ==> Kfree
	rt_set_variable_malloc(Kmalloc);
	rt_set_variable_free(Kfree);
	rt_set_malloc(Kmalloc);
	rt_set_free(Kfree);

	// [@yuza-lab] nnablart: init C runtime
	void *context = nnablart_mainruntime_allocate_context(MainRuntime_parameters);
	tm_printf("ai)Detector %d %d\n", NNABLART_MAINRUNTIME_INPUT0_SIZE, NNABLART_MAINRUNTIME_OUTPUT0_SIZE);
	float* input_buf = nnablart_mainruntime_input_buffer(context, 0);
	float* output_buf = nnablart_mainruntime_output_buffer(context, 0);

	UW*	input_buf_p = (UW*)input_buf;
	UW* output_buf_p = (UW*)output_buf;
	float cmp_buf = 0.2f;					// [@yuza-lab]　姿勢判定閾値…本サンプルNNでは出力値を観察して設定する必要がある
	UW cmp_buf_p = *(UW *)&cmp_buf;

	iicsetup(TRUE);								// I2Cドライバ起動(※B)

	dat = read_reg(IICADR_ACC, WHO_AM_I_A);		// WHO_AM_I_Aの読み出し(※C)
	tm_printf("WHO_AM_I_A = 0x%02x\n", dat);

	write_reg(IICADR_ACC, CTRL_REG1_A,  0x57);	// ODR=5, LPen=0(※D)

	dat = read_reg(IICADR_ACC, CTRL_REG1_A);	// CTRL_REG1_Aの読み出し(※E)
	tm_printf("CTRL_REG1_A = 0x%02x\n\n", dat);

	for(;;){
		// X軸、Y軸、Z軸の上位バイトと下位バイトをまとめて読み出す(※F)
		err = read_reg_6(IICADR_ACC, OUT_X_L_A, outreg);

		// get_acc10bitによる後処理
		x_acc = get_acc10bit(outreg[0], outreg[1]);
		y_acc = get_acc10bit(outreg[2], outreg[3]);
//		z_acc = get_acc10bit(outreg[4], outreg[5]);		// [@yuza-lab] v0.93.0, z軸データ不使用

//		tm_printf("Acc: x,y,z=%4d,%4d,%4d\n", x_acc, y_acc, z_acc);		// [@yuza-lab] v0.93.0

		// [@yuza-lab] nnablart: 入力～推論～出力…小数点表示すべきだが，検証不足につきhexパターン生出力
		tm_putstring("\n==sampling==\n");
		tm_printf("acc) %x(%d), %x(%d)\n", x_acc, x_acc, y_acc, y_acc);
		tm_putstring("--ai--\n");
		*(input_buf) = x_acc;
		*(input_buf + 1) = y_acc;
		tm_printf("ai_input) %x, %x\n", *input_buf_p, *(input_buf_p + 1));
		nnablart_mainruntime_inference(context);		// [@yuza-lab] nnablart: 推論
		tm_printf("ai_output) %s, %x, %x\n", *output_buf < cmp_buf ? "Uplight" : "Lay", *output_buf_p, cmp_buf_p);

//		nnablart_mainruntime_free_context(MainRuntime_parameters);		// [@yuza-lab] nnablart: リソース開放…本サンプルでは使わない

//		tk_dly_tsk(500);       // 約500ミリ秒の周期で永久に繰り返し
		tk_dly_tsk(2000);      // 約2000ミリ秒の周期で永久に繰り返し		// [@yuza-lab] v0.93.0
	}
}
