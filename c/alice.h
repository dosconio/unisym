// ASCII,GB Arina_habit_slice C99 TAB4
/*
	Copyright 2023 ArinaMgk

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#ifndef ArnHabit
#define ArnHabit

#define nil 0
#define nop 0x90

#define masm __asm

#define print(x) printf("%s",(x));
#define printline(x) printf("%s\n",(x));
#define pll(x,y)   printf("%s : %llx\n",(x),(y));
#define pd(x) printf("%d\n",(x));

#define concur(r,c) (r*cols+c)// ConsoleCursor

#if !defined(uint)&&!defined(_Linux)// avoid GCC duplicate ��unsigned��
	#define uint unsigned int
#endif
#define llong long long int
#define sll signed long long int
#define ullong unsigned long long int
#define ull unsigned long long int
#define byte unsigned char
#define word unsigned short int
#define dword unsigned int
#define stduint size_t
#define stdint ptrdiff_t

#define AlignEven(x) ((x)+1)&(~1)// {Q} the size of ~1 may be flexible

#define jump goto
#define call(x) (x)()

// These IF can avoid error such as mixing "a=0" and "a==0"
#define If(con) if(0||con)
#define If_(con) if(1&&con)
#define RNZ(a) {if(a) return (a);}// Return if not zero
#define RZ(a) {if(!a) return (a);}// Return if zero

#define idle() {jump: goto jump;}

#define zalloc(x) calloc((x),1)// Zero Alloc

// Added RFW24, Exchange
#define xchg(a,b) (a)^=(b)^=(a)^=(b)
#define xchgptr(a,b) *(size_t*)&(a)^=*(size_t*)&(b)^=*(size_t*)&(a)^=*(size_t*)&(b)

#ifndef max//(a,b)
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#define MAX(d,s) if((d)<(s)){(d)=(s);}
#ifndef min//(a,b)
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#define MIN(d,s) if((d)>(s)){(d)=(s);}
// ---- ---- algorithm ---- ----
#define isodd(x) ((x)&1)
#define iseven(x) !((x)&1)
#define isZeroMantissa(flt) ((int)(flt)==(flt)) // RFW23

#define chars_stack(x) &(char[]){#x "\0"}// chars_stack(123)
#define chstk chars_stack

// ARINA-COVE C23-STYLE Attribute
#define _Heap
#define _Need_free _Heap
#define _Heap_tmpher// The function with _Heap_tmpher should not call each other

#define AddDecimalDigitsLen(i,num) do{(i)++;(num)/=10;}while(num)// e.g. for "0" is 1, "12" is 2

///#define foreachstr(iden,x) for(char iden, *iden#ptr=(char*)(x);iden=*iden#ptr;iden#ptr++)// {why} error tip yo VSCODE::IntelliSenseMode(GCC)
#define for0(iden,times) for(size_t iden=0;iden<(times);iden++)
#define for1(iden,times) for(size_t iden=1;iden<=(times);iden++)

#ifdef _MSC_VER// for MSVC
#define __FUNCIDEN__ __FUNCDNAME__
#elif defined(__GNUC__)
#define __FUNCIDEN__ __func__// cannot auto-strcat
#endif


#endif
// more to see "aldbg.h"
// ---- ---- ---- ---- ---- ---- ---- ----

