/**
 * @file    pltm_syscall.c
 * @brief   NNabla C Runtime 向け syscall.c 代替ソース
 * Project: micro:bit de TinyML♪
 * @author  ゆざ (@yuza-lab)
 * @version v0.93.0
 * @date    2025-04-04 (Created)
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

//#include <errno.h>		/* [@yuza-lab] errnoではなくuT-Kernel 3.0のエラーコードを返すように実装 */
#include <tk/tkernel.h>

#include "pltm_stat.h"

int _close(int file) {
//    errno = EBADF;		// Bad file number
//    return -1;
	return E_NOMDA;
}

int _fstat(int file, struct stat *st) {
//    errno = EBADF;
//    return -1;

	// ダミーの struct stat 型に値を設定
	st->st_dev = 0;
	st->st_ino = 0;

	return E_NOMDA;
}

int _isatty(int file) {
//    errno = EBADF;
//    return 0;
	return E_NOMDA;
}

int _lseek(int file, int ptr, int dir) {
//    errno = EBADF;
//    return -1;
	return E_NOMDA;
}

int _open(const char *name, int flags, int mode) {
//    errno = EACCES;		// Permission denied
//    return -1;
    return E_IO;
}

int _read(int file, char *ptr, int len) {
//    errno = EBADF;
//    return -1;
	return E_NOMDA;
}

//caddr_t _sbrk(int incr) {
////    return (caddr_t) -1;
//	return E_IO;
//}
void * _sbrk(int incr) {
	return (void *) E_NOMEM;
}

int _write(int file, char *ptr, int len) {
//    errno = EBADF;
//    return -1;
	return E_NOMDA;
}

int _kill(int pid, int sig) {
//    errno = EINVAL;		// Invalid argument
//    return -1;
	return E_NOEXS;
}

int _getpid(void) {
//    return -1;
	return E_ID;
}

void _exit(int status) {
    while (1);
}
