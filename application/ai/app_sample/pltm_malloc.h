/**
 * @file    pltm_malloc.h
 * @brief   NNabla C Runtime 向け malloc 代替ソース
 * Project: micro:bit de TinyML♪
 * @author  ゆざ (@yuza-lab)
 * @version v0.93.0
 * @date    2025-04-05 (Created)
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

#ifndef APP_SAMPLE_PLTM_MALLOC_H_
#define APP_SAMPLE_PLTM_MALLOC_H_

#include <tk/syslib.h>

#define	malloc	Kmalloc
#define	free	Kfree

#endif /* APP_SAMPLE_PLTM_MALLOC_H_ */
