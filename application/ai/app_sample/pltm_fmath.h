/**
 * @file    pltm_fmath.h
 * @brief   NNabla C Runtime 向け float 演算関数群の定義（プロトタイプ宣言）
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

#ifndef APP_SAMPLE_PLTM_FMATH_H_
#define APP_SAMPLE_PLTM_FMATH_H_

IMPORT float expf(float x);
IMPORT float tanhf(float x);
IMPORT float logf(float x);
IMPORT float powf(float base, float exponent);
IMPORT float fabsf(float x);
IMPORT float log2f(float x);
IMPORT float roundf(float x);
IMPORT float fminf(float x, float y);
IMPORT float fmaxf(float x, float y);
IMPORT float sqrtf(float x);
IMPORT BOOL isnan(float f);
IMPORT BOOL isinf(float f);

#endif /* APP_SAMPLE_PLTM_FMATH_H_ */
