/**
 * @file    pltm_fmath.c
 * @brief   NNabla C Runtime 向け float 演算関数群の実装
 * Project: micro:bit de TinyML♪
 * @author  ゆざ (@yuza-lab)
 * @version v0.93.0
 * @date    2025-04-03 (Created)
 */

/*
 * Copyright (c) 2025 ゆざ (@yuza-lab). All Rights Reserved.
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

EXPORT float expf(float x) {
    float result = 1.0f;
    float term = 1.0f;
    for (int i = 1; i < 10; ++i) { // 10項まで計算 (精度に応じて調整)
        term *= x / i;
        result += term;
    }
    return result;
}


EXPORT float tanhf(float x) {
    float exp_2x = expf(2.0f * x);
    return (exp_2x - 1.0f) / (exp_2x + 1.0f);
}


EXPORT float logf(float x) {
    // ここでは logf() の簡易的な実装例を示す
    // 実際の logf() はより複雑な計算が必要
    float result = 0.0f;
    float term = (x - 1.0f) / x;
    float power = term;
    for (int i = 1; i < 10; ++i) {
        result += power / i;
        power *= term;
    }
    return result;
}


EXPORT float powf(float base, float exponent) {
    return expf(exponent * logf(base));
}


EXPORT float fabsf(float x) {
    unsigned int *ptr = (unsigned int *)&x;
    *ptr &= 0x7FFFFFFF; // 符号ビットをクリア
    return x;
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
