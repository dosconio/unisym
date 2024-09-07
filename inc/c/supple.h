// ASCII C TAB4 CRLF
// Docutitle: Supplement and Complement
// Codifiers: @dosconio: 20240603
// Attribute: Arn-Covenant Any-Architect Env-Freestanding Non-Dependence
// Copyright: UNISYM, under Apache License 2.0
/*
	Copyright 2023 ArinaMgk

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0
	http://unisym.org/license.html

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#ifndef _INC_COMPLEMENT
#define _INC_COMPLEMENT

#include "stdinc.h"

// ---- { STDC:: stdarg.h } 20240824 ----
// by makeing use of stack(BP) and C calling convention

typedef struct {
	unsigned char* stack_ptr;
} para_list;

#define _para_align(type) (((sizeof(type) + sizeof(stduint) - 1) / sizeof(stduint)) * sizeof(stduint))

#define para_ento(ap, param) (ap.stack_ptr = (unsigned char *)&param + sizeof(stduint))

#define para_next(ap, type) (*(type *)((ap.stack_ptr += _para_align(type)) - _para_align(type)))

#define para_endo(ap) (ap.stack_ptr = NULL)// optional now

#define Letpara(argiden, cdecl_iden) para_list argiden; para_ento(argiden, cdecl_iden);// we can use as uni::Letpara

#define para_copy(dest, src, type) MemCopyN((void *)&dest, (void *)&src, _para_align(type))

/* EXAMPLE
void print_numbers(int count, ...) {
	Letpara(args, count);
	for0 (i, count) {
		printf("%x\n", para_next(args, int));
	}
}
*/

// ---- { STDC:: setjmp.h } 20240902 (Win32) ----

typedef struct {
	uint32 ret;
	uint32 ebx;
	uint32 esi;
	uint32 edi;
	uint32 ebp;
	uint32 esp;
} Retpoint;

extern pureptr_t MarkPoint(Retpoint* buf);
extern void JumpPoint(const Retpoint* buf, pureptr_t val);

//#define setjmp MarkPoint
//inline static void longjmp(jmp_buf buf, int v) { JumpPoint(&buf, v); }

/* EXAMPLE #include <c/supple.h>
static Retpoint env;
void test_func() {
	JumpPoint(&env, "ciallo");
}
int main() {
	pureptr_t val;
	val = MarkPoint(&env);
	if (!val) {
		test_func();
	} else {
		printf("Returned from longjmp, val = %s\n", val);
	}
}
*//*
aasm -f win32 %ulibpath%\asm\x86\jump.asm -o setjmpS.o -g
gcc -m32 -o a.exe test.c setjmpS.o -g -I%uincpath%
EXPECTED>a.exe
Returned from longjmp, val = ciallo
*/

// ---- { MORE } ----

#endif
