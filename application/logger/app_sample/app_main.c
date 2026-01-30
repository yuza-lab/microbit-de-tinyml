/**
 * @file    app_main.c
 * @brief   [I2C経由の加速度センサーの動作確認(μT-Kernel 3.0用)]の改変実装～TinyML教師ラベル付データ取得
 * Project: micro:bit de TinyML♪
 * @author  T3 WG of TRON Forum (Original Author)
 * @author  Modified by ゆざ (@yuza-lab)
 * @version v0.93.0
 * @date    2025-03-07 (Created)
 * @details
 * 【ライセンスに関する注意 / License Notice】
 * - 本ファイルは「TRONWARE VOL.207」 (パーソナルメディア刊) 掲載の記事コードをベースに改変したものです．
 * - 本ファイルの改変部分 (Modified by ゆざ) については，Apache License, Version 2.0 を適用します．
 * - パーソナルメディア株式会社 出版部よりソースコードの改変ならびに一般公開について許諾を得ております．
 * - オリジナル部分のライセンスについては，原典の規定に従います．
 * 【改変内容 / Modification Details】
 * - 加速度センサデータおよびボタン押下情報などをログ出力…用途：TinyML教師ラベル付データ取得
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

/**
 * @brief	ボード上のbtn_aとbtn_bを有効化
 * @note	Added by [@yuza-lab] for v0.93.0
 */
LOCAL void btn_init(void)
{
	out_w(GPIO(P0, PIN_CNF(14)), 0);	// btn_a
	out_w(GPIO(P0, PIN_CNF(23)), 0);	// btn_b
}

//---------------------------------------------------------------
EXPORT void usermain( void )
{
	INT	dat, x_acc, y_acc, z_acc;
	UB	outreg[6];
	ER	err;

	// [@yuza-lab] v0.93.0, btn_aとbtn_bを有効化
	UW		gpio_p0in;
	BOOL	btn_a, buff_btn_a, btn_b, buff_btn_b;
	INT		btn_stat, cnt_0, cnt_1;

	iicsetup(TRUE);								// I2Cドライバ起動(※B)

	dat = read_reg(IICADR_ACC, WHO_AM_I_A);		// WHO_AM_I_Aの読み出し(※C)
	tm_printf("WHO_AM_I_A = 0x%02x\n", dat);

	write_reg(IICADR_ACC, CTRL_REG1_A,  0x57);	// ODR=5, LPen=0(※D)

	dat = read_reg(IICADR_ACC, CTRL_REG1_A);	// CTRL_REG1_Aの読み出し(※E)
	tm_printf("CTRL_REG1_A = 0x%02x\n\n", dat);

	// [@yuza-lab] v0.93.0, btn初期化＆押下カウンタ
	btn_init();
	cnt_0 = 0;		// カウンタ…btn_stat = 0
	cnt_1 = 0;		// カウンタ…btn_stat = 1

	for(;;){
		// [@yuza-lab] v0.93.0, ボタン状態：リセット
		btn_a = FALSE;
		buff_btn_a = FALSE;
		btn_b = FALSE;
		buff_btn_b = FALSE;

		// X軸、Y軸、Z軸の上位バイトと下位バイトをまとめて読み出す(※F)
		err = read_reg_6(IICADR_ACC, OUT_X_L_A, outreg);

		// [@yuza-lab] v0.93.0, ボタン状態：取得
		gpio_p0in = in_w(GPIO(P0, IN));
		btn_a = ((gpio_p0in & (1 << 14)) == 0);
		btn_b = ((gpio_p0in & (1 << 23)) == 0);

		// get_acc10bitによる後処理
		x_acc = get_acc10bit(outreg[0], outreg[1]);
		y_acc = get_acc10bit(outreg[2], outreg[3]);
//		z_acc = get_acc10bit(outreg[4], outreg[5]);		// [@yuza-lab] v0.93.0, z軸データ不使用

		// [@yuza-lab] v0.93.0, ボタン状態：弁別
		buff_btn_a = buff_btn_a | btn_a;
		buff_btn_b = buff_btn_b | btn_b;

		if (buff_btn_a) {
			// ボード：水平
			btn_stat = 0;
			cnt_0 ++;
		} else if (buff_btn_b) {
			// ボード：直立
			btn_stat = 1;
			cnt_1 ++;
		} else {
			// ボード：その他
			btn_stat = 2;
		}

//		tm_printf("Acc: x,y,z=%4d,%4d,%4d\n", x_acc, y_acc, z_acc);
		tm_printf("%4d,%4d,%2d,(%d:%d)\n", x_acc, y_acc, btn_stat, cnt_0, cnt_1);	// [@yuza-lab] v0.93.0, 加速度センサ値X-Y，教師ラベル（姿勢），教師ラベル別データ取得数0-1

//		tk_dly_tsk(500);       // 約500ミリ秒の周期で永久に繰り返し
		tk_dly_tsk(100);       // [@yuza-lab] v0.93.0, 100msec
	}
}
