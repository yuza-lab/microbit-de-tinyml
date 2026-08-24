/**
 * @file    pltm_fmath.c
 * @brief   NNabla C Runtime 向け float 演算関数群の実装
 * Project: micro:bit de TinyML♪
 * @author  ゆざ (@yuza-lab)
 * @version v0.93.1
 * @date    2025-04-03 (Created)
 */

/*
 * Copyright (c) 2025-2026 ゆざ (@yuza-lab). All Rights Reserved.
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
 */

#include <tk/tkernel.h>

// 単精度浮動小数点数をビット操作するための共用体
typedef union {
	float f;
	UW i;
} float_bits_t;

EXPORT float expf(float x) {
	// 各種定数
	const float LOG2E = 1.4426950408889634f;	// 1 / ln(2)
	const float LN2_HI = 0.69314718f;			// ln(2) の上位ビット
	const float LN2_LO = 1.90821493e-10f;		// ln(2) の下位ビット（精度確保用）

	// 1. オーバーフロー・アンダーフローのクランプ処理 (SoftmaxのNaN発散対策)
	if (x <= -87.33654f) return 0.0f;
	if (x >= 88.72283f) return 3.4028234e38f;	// floatの最大値付近

	// 2. レンジリダクション: x を k * ln(2) + r に分解する
	// これにより，計算が難しい e^x を「2^k * e^r」に変換する．(r は非常に0に近い値になる)
	float k_float = x * LOG2E;

	int k;
	if (k_float >= 0.0f) {
		k = (int)(k_float + 0.5f);
	} else {
		k = (int)(k_float - 0.5f);
	}

	float k_f = (float)k;

	// 精度落ちを防ぐため，ln(2)をHIとLOに分けて引き算
	float r = (x - k_f * LN2_HI) - k_f * LN2_LO;

	// 3. テイラー展開(マクローリン展開)の Horner法による多項式近似
	// e^r ≒ 1 + r + r^2/2! + r^3/3! + r^4/4! + r^5/5!
	float r2 = r * r;
	float poly = 1.0f + r + r2 * (0.5f + r * (0.166666667f + r * (0.041666667f + r * 0.008333333f)));

	// 4. 高速な 2^k の乗算 (IEEE754の指数部を直接足算して実現)
	float_bits_t u;
	u.f = poly;
	u.i += ((UW)k << 23); // floatの指数部(23ビットシフト)にkを加算

	return u.f;
}


EXPORT float tanhf(float x) {
    float exp_2x = expf(2.0f * x);
    return (exp_2x - 1.0f) / (exp_2x + 1.0f);
}


EXPORT float logf(float x) {
	if (x <= 0.0f) {
		return -1e30f; // 負数・ゼロ対策（マイナス無限大の代わりに十分小さな値）
	}
	float_bits_t u;
	u.f = x;

	// 1. 指数部(Exponent)の抽出 (IEEE 754: ビット23〜30)
	W e = (W)((u.i >> 23) & 0xFF) - 127;

	// 2. 仮数部(Mantissa)を [1.0, 2.0) の範囲に正規化
	u.i = (u.i & 0x007FFFFF) | 0x3F800000;
	float m = u.f;

	// 3. 多項式近似による ln(m) の計算 (m は 1.0 〜 2.0 の範囲)
	// 精度を上げるための多項式 (Remezアルゴリズム等による最適化の簡易版)
	// y = (m - 1) / (m + 1) を使う方法などもあるが，今回はシンプルな多項式で構成
	float t = (m - 1.0f) / (m + 1.0f);
	float t2 = t * t;

	// 奇数次の項を展開 (ln((1+t)/(1-t)) = 2 * (t + t^3/3 + t^5/5 + ...))
	float sum = t * (2.0f + t2 * (0.666666666f + t2 * (0.4f + t2 * 0.285714286f)));

	// 4. 指数部を結合: ln(x) = ln(m) + e * ln(2)
	LOCAL CONST float LN2 = 0.6931471805599453f;
	return sum + (float)e * LN2;
}


EXPORT float log2f(float x) {
    unsigned int *ptr = (unsigned int *)&x;
    unsigned int exponent = ((*ptr) >> 23) & 0xFF; // 指数部を取得
    unsigned int mantissa = (*ptr) & 0x7FFFFF; // 仮数部を取得

    if (exponent == 0) {
        // x が非正規化数または 0 の場合
        return E_PAR;		// -INFINITY; // または適切なエラー処理
    } else if (exponent == 0xFF) {
        // x が無限大または NaN の場合
        return E_PAR; 		//	x; // または適切なエラー処理
    }

    float result = (float)(exponent - 127); // 指数部から結果を計算

    // 仮数部を補正 (簡易的な近似)
    result += (float)mantissa / 0x800000;

    return result;
}


EXPORT float log10f(float x) {
	// log10(x) = ln(x) / ln(10)
	// 1.0f / ln(10) はコンパイル時定数として最適化される
	LOCAL CONST float INV_LN10 = 0.4342944819032518f;
	return logf(x) * INV_LN10;
}


EXPORT float powf(float base, float exponent) {
    return expf(exponent * logf(base));
}


EXPORT float fabsf(float x) {
    unsigned int *ptr = (unsigned int *)&x;
    *ptr &= 0x7FFFFFFF; // 符号ビットをクリア
    return x;
}


EXPORT float roundf(float x) {
    if (x >= 0.0f) {
        return (float)((int)(x + 0.5f));
    } else {
        return (float)((int)(x - 0.5f));
    }
}


EXPORT float fminf(float x, float y) {
    if (x != x) { // x が NaN の場合
        return y;
    }
    if (y != y) { // y が NaN の場合
        return x;
    }
    return (x <= y) ? x : y;
}


EXPORT float fmaxf(float x, float y) {
    if (x != x) { // x が NaN の場合
        return y;
    }
    if (y != y) { // y が NaN の場合
        return x;
    }
    return (x >= y) ? x : y;
}


EXPORT float sqrtf(float x) {
    if (x < 0.0f) {
        return E_PAR; 		//	NAN; // 負の数の平方根は NaN
    }

    if (x == 0.0f) {
        return 0.0f;
    }

    float guess = x; // 初期推定値
    for (int i = 0; i < 10; ++i) { // 10回反復 (精度に応じて調整)
        guess = 0.5f * (guess + x / guess);
    }
    return guess;
}


// NaNの判定
EXPORT BOOL isnan(float f)
{
    union {
        float f;
        UW u;
    } temp = {f};

    // 指数部の8ビットがすべて1 (0xFF) かどうかをチェック (ビット30-23)
    // 0x7F800000 は、仮数部を無視した、指数部が全て1の最小値
    if ((temp.u & 0x7F800000) == 0x7F800000) {
        // 仮数部 (ビット22-0) がゼロではない (NaNの条件) かどうかをチェック
        // 仮数部がゼロなら +/-Inf、ゼロ以外なら NaN
        if ((temp.u & 0x007FFFFF) != 0) {
            return TRUE;
        }
    }
    return FALSE;
}


// 無限大の判定
EXPORT BOOL isinf(float f)
{
    union {
        float f;
        UW u;
    } temp = {f};

    // 指数部がすべて1 (0xFF) かどうかをチェック
    if ((temp.u & 0x7F800000) == 0x7F800000) {
        // かつ、仮数部がすべてゼロかどうかをチェック (Infの条件)
        if ((temp.u & 0x007FFFFF) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}
