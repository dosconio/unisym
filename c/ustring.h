// ASCII TAB4 C99 ArnAssume
// Operations for string of ASCII character and node
// E X P O S T U ** DO NOT TRAP IN C TOO MUCH! BE YOURSELF. ** L A T I O N //
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
/* Component
* node-family{node, dnode, tnode, nnode}
* common heap operations
* strpool
* Buf-special part
* General String Function
* ChrAr
* Temporarily Stage Area
*/
#define _LIB_STRING

#ifndef _LIB_STRING_ONCE_HEAD
#define _LIB_STRING_ONCE_HEAD
	#ifndef _INC_STDDEF
	#include <stddef.h>
	#endif
	#include "alice.h"
	#include "aldbg.h"

struct ArinaeFlag
{
	unsigned PrecLoss : 1,// <OUT>
		Failure : 1,// <OUT>
		Signed : 1,// <IN>
		Sign : 1,// <OUT>
		Dbg : 1;// <IN> kept for the future
};extern struct ArinaeFlag arna_eflag;
#define aflag arna_eflag

//single-direction simple node
typedef struct Node
{
	struct Node* next;
	char* data;
} Node, node;

// double-directions node
typedef struct Dnode
{
	struct Dnode* left;// lower address
	char* addr;// for order
	union { size_t len, type; };// non-order
	union { struct Dnode* next, * right; };// higher address
} Dnode, dnode;// recommand using dnode

typedef enum TokType
{
	tok_EOF = 0,// -1 or 0
	tok_any,
	tok_string,// "Hallo"
	tok_comment,// //
	tok_directive,// #include
	tok_number,// 1
	tok_sym,// +-*/
	tok_iden,// identifier
	tok_space,// ' ' or \t or excluding new-line
	tok_else,
} TokType, toktype;// the counts should not be greater than 15.

typedef struct TokenNode
{
	// struct Dnode;
	struct TokenNode* left;
	union { char* addr; size_t index; };
	union { size_t len; TokType type; };
	union { struct TokenNode* next, * right; };
	// [ L | AD & L/T | R ]
	size_t row, col;
} Toknode, Tode, tode, tnode;// recommand using tnode

typedef struct TreeNode
{
	// no use of union for grace view of debug
	struct TreeNode* left;
	char* addr;
	size_t class;
	struct TreeNode* right;
	size_t row, col;
	//
	struct TreeNode* subf;// sub-first-item
	void* bind;
	size_t flag;
} Nesnode, nnode;// recommand using nnode

#endif
//
//
//
#if defined(_LIB_STRING_BUFFER) && !defined(_LIB_STRING_BUFFER_GUARD)// bstring.c, need pre-set buffer
#define _LIB_STRING_BUFFER_GUARD
	extern char arna_tempor[];// as result
	extern char arna_tmpslv[];// Do not use as result, same size with tempor.
	extern char arna_tmpext[];

#endif
//
//
//
#if defined(_LIB_STRING_HEAP) && !defined(_LIB_STRING_HEAP_GUARD)// hstring.h, any need to allocate memory
	#define _LIB_STRING_HEAP_GUARD
//---- ---- ---- ---- node ---- ---- ---- ----
	Node* NodeCreate(Node* previous, const char* data);
	Node* NodeCreateOrder(Node* previous, const char* data);
	size_t NodeIndex(Node* first, const char* cmp);
	size_t NodeCount(Node* first);
	Node* NodeInsert(Node* obj, const char* data);
	void NodesRelease(Node* first);
	
//---- ---- ---- ---- dnode ---- ---- ---- ----
	Dnode* DnodeCreate(Dnode* any, char* addr, size_t len);
	Dnode* DnodeRewind(Dnode* any);
	size_t DnodeCount(Dnode* any);
	void DnodeRelease(Dnode* some, int tofree);
	void DnodesRelease(Dnode* first, int tofree);

//---- ---- ---- ---- tnode ---- ---- ---- ----
	Toknode* StrTokenAll(int (*getnext)(void), void (*seekback)(ptrdiff_t chars), char* buffer);
	void StrTokenClearAll(Toknode* tstr);
	void StrTokenThrow(Toknode* one);// a b c --> a c
	inline static Toknode* StrTokenBind(Toknode* left, Toknode* mid, Toknode* right)
	{
		if (left) left->next = mid;
		if (mid) mid->next = right;
		if (right) right->left = mid;
		if (mid) mid->left = left;
	}

	#define StrTokenPrint(first)\
		printf("Token: [R %llu,C %llu][%s] %s\n", first->row, first->col,\
			((const char* []){"END", "ANY", "STR", "CMT", "DIR", "NUM", "SYM", "IDN", "SPC", "ELS"})\
			[first->type], first->type == tok_space ? "" : first->addr);

	// For the string of the Tode.
	#define StrTokenPrintAll(first)\
		do StrTokenPrint(first);\
		while (first = first->next);

//---- ---- ---- ---- common heap operations ---- ---- ---- ----
	
	inline static char* StrHeapFromChar(char c)// Convert char in string in heap
	{
		char* ptr = salc(2);
		*ptr = c;
		return ptr;
	}
	char* StrHeap(const char* valit_str);
	void* MemHeap(const void* sors, size_t byteof);
	char* StrHeapN(const char* valit_str, size_t strlen);
	char* StrHeapAppend(const char* dest, const char* sors);
	char* StrHeapAppendN(const char* dest, const char* sors, size_t n);
	char* StrReplace(const char* dest, const char* subfirstrom, const char* subto, size_t* times);
	char* StrHeapInsertThrow(const char* d, const char* s, size_t posi, size_t thrown);
	// posi_start and later positions of string move into the lower endian RFE02:16

	char* instoa(ptrdiff_t num);// [Instant to ASCII yo heap]

//---- ---- ---- ---- strpool ---- ---- ---- ----
	/* ROUTINE EXAMPLE
		StrPoolInit();
		atexit(StrPoolRelease);
		printf("%s", str = StrPoolHeap("Hello,world!"));
	*/
	#define _ModString_Strpool_UNIT_SIZE 4096// A page align by default

	void StrPoolInit();
	char* StrPoolHeap(const char*, size_t);
	char* StrPoolAlloc(size_t);
	char* StrPoolAllocZero(size_t);
	void StrPoolRelease();

#endif// !HEAP-PART
//
// Buf-special part
//
#if (defined _LIB_STRING_BUFFER) && !(defined _LIB_STRING_HEAP) && defined(_LIB_STRING_BUFFER_0HEAP_GUARD)// {TODO}GUARD
	#define _LIB_STRING_BUFFER_0HEAP_GUARD
	#define ChrAdd ChrAddBuf
	#define ChrSub ChrSubBuf
	#define ChrMul ChrMulBuf
	#define ChrDiv ChrDivBuf
	#define stradd ChrAdd
	#define strsub ChrSub
	#define strmul ChrMul
	#define instoa instob
	// {TODO}...
//ChrHexToDecBuf

	
#endif// End of Buf-special part
//
// General String Function
//
#ifndef _LIB_STRING_ONCE_TAIL
#define _LIB_STRING_ONCE_TAIL

static inline char* MemRelative(char* addr, size_t width, ptrdiff_t times)
{
	register size_t i = 0;
	if (width == 0 || times == 0) return addr;
	if (times < 0) while (i < width) { *(addr + i + times) = addr[i]; i++; }
	else while (i < width) { addr[width + times - i - 1] = addr[width - i - 1]; i++; }
	return addr + times;
}/* Update: Arina fixed REC06 */

static inline char* MemAbsolute(char* dest, const char* sors, size_t width)
{
	register size_t i = 0;
	if (dest < sors) while (i < width) { dest[i] = sors[i]; i++; }
	else while (i < width) { dest[width - 1 - i] = sors[width - 1 - i]; i++; }
	return dest;
}/* Update: Arina fixed REC06 */

static inline char* StrCopy(char* dest, const char* sors)
{
	register char* d = dest;
	while (*d++ = *sors++); return dest;
}

static inline void* MemSet(void* s, int c, size_t n)
{
	while (n) { n--; ((char*)s)[n] = (char)c; }
	return s;
}

// RFB31 changed from `static inline char* MemCopyN(char* dest, const char* sors, size_t n)`
static inline char* MemCopyN(void* dest, const void* sors, size_t n)
{
	register char* d = (char*)dest;
	while (n--) *d++ = *(*((const char**)&sors))++;
	return dest;
}

// n excludes terminating-0
static inline char* StrCopyN(char* dest, const char* sors, size_t n)
{
	register char* d = dest;
	if (!sors)goto endo;
	while (n && (*d++ = *sors++)) n--;
	*d = 0;
endo:
	return dest;
}

static inline char* StrAppend(char* dest, const char* sors)
{
	register char* d = dest;
	while (*d) { d++; };
	while (*d++ = *sors++);
	return dest;
}

static inline char* StrAppendN(char* dest, const char* sors, size_t n)
{
	register char* d = dest;
	while (*d) { d++; };
	while (n && (*d++ = *sors++)) n--;
	if (!n) *d = 0;
	return dest;
}

/* COMPARE */

static inline int MemCompare(const char* a, const char* b, size_t n)
{
	register char tmp = 0;
	while (n && !(tmp = (*a - *b))) n--; return (int)tmp;
}

static inline int StrCompare(const char* a, const char* b)
{
	int tmp = 0;
	while (!(tmp = (*a - *b)) && *a++ && *b++); return tmp;
}

static inline int StrCompareN(const char* a, const char* b, size_t n)
{
	int tmp; tmp = 0;// MSVC' red tape
	while (n && !(tmp = (*a - *b)) && *a++ && *b++) n--; return tmp;
}

// RFV12 Updated.
static inline size_t StrLength(const char* s)
{
	register size_t len = 0;
	while (s[len]) len++;
	return len;
}

static inline char* StrElement(char* s, ptrdiff_t idx)
{
	// a  b  c  [\0]
	// +0 +1 +2 +3
	// -3 -2 -1
	if (!s || !*s)return 0;
	int sign = 0;
	size_t len = 0;
	while (s[len]) len++;
	if (idx > 0) if ((size_t)idx >= len) return 0;
	if (idx < 0) if ((size_t)(-idx) > len) return 0;
	return (idx < 0) ? s + len + idx : s + idx;
}

static inline char StrCharLast(const char* s)//= *StrElement(s, -1)
{
	if (!s)return 0;
	while (*s) s++;
	return *(s-1);
}

static inline const char* MemIndexByte(const char* s, int c, size_t n)
{
	while (n--) { if (*s == c) return s; else s++; } return NULL;
}

static inline const char* StrIndexChar(const char* s, int c)
{
	register char tmp;
	do if ((tmp = *s) == c) return s; else s++; while (tmp);
	return NULL;
}

static inline const char* StrIndexCharRight(const char* s, int c)
{
	register char tmp; const char* res = 0;
	do if ((tmp = *s) == c) res = s++; else s++; while (tmp);
	return res;
}

// RFV07 Rename from "StrLenSameChar"
static inline size_t StrLengthSameChar(const char* str, int c, const char** ret)
{
	// subord of StrSpanInclude()
	const char* p = str;
	size_t len;
	while (1) if (*p == c)
	{
		len = 1;
		while (p[len] == c)len++;
		*ret = p;
		return len;
	}
	else if (!*p) break; else p++;
	*ret = 0;
	return 0;
}// A.R.I.N.A.

static inline const char* StrIndexString(const char* dest, const char* sub)
{
	register size_t len;
	while (*dest) { len = 0; while ((sub[len] == dest[len]) && (sub[len])) len++; if (!sub[len]) return dest; dest++; }
	return NULL;
}

static inline size_t StrSpanInclude(const char* s1, const char* s2)
{
	size_t res = 0; register size_t offs; register char c;
	while (c = *s1++) { offs = 0; while ((s2[offs]) && (s2[offs] != c)) offs++; if (!s2[offs]) return res; res++; }
	return res;
}

static inline size_t StrSpanExclude(const char* s, const char* reject)
{
	size_t ret = 0;
	register const char* ecx; char TmpChar, TmpElement;
	while (TmpChar = *s++) { ecx = reject; while (TmpElement = *ecx++) if (TmpElement == TmpChar)   return ret--; ret++; }
	return ret;
}

static inline const char* StrIndexChars(const char* s1, const char* s2)
{
	register char c; size_t offs;
	while (c = *s1) { offs = 0; while (s2[offs]) if (s2[offs++] == c) return s1; s1++; } return NULL;
}

void StrFilterOut(char* p, char c);
void StrFilter(char* p, enum TokType tt);//TODO. no considering new-line
void StrFilterString(char* p, const char* needs);
void StrFilterOutString(char* p, const char* neednot);

static inline char* StrTokenOnce(char* s1, const char* s2)
{
	static char* _ModString_StrTokenOnce;// na StrToken, Arina updated yo RFT02.
	if (!s1) if (_ModString_StrTokenOnce) s1 = _ModString_StrTokenOnce; else return NULL;
	register size_t offs;
	/*Skip prefix*/ while (*s1) {
		offs = 0; while (s2[offs]) {
			if (s2[offs] == *s1) break; offs++;
		} if (!s2[offs]) break; s1++;
	}
	_ModString_StrTokenOnce = s1;
	while (*s1++)
	{
		offs = 0; while (s2[offs]) { if (s2[offs] == *s1) { *s1 = 0; s2 = _ModString_StrTokenOnce; _ModString_StrTokenOnce = s1 + 1; return (char*)s2; }; offs++; }
	} s2 = _ModString_StrTokenOnce;
	_ModString_StrTokenOnce = 0;
	return (char*)s2;
}

#define StrSubWithdraw(posi_start,len)\
	MemRelative((posi_start), StrLength(posi_start) + 1, -(ptrdiff_t)(len))

char* instob(ptrdiff_t num, char* buf);
ptrdiff_t atoins(const char* str);

//
// Char-unit Arithmetic
//
// Having brewed about 2 years since 2022 Aug.


size_t ChrCpz(char* str);// Clear prefix zeros, "+001"-->"+1".

// Char-Arithmetic Cut Trailing zeros. Return the counts of chars that have been cut.
size_t ChrCtz(char* str);

#ifdef _LIB_STRING_HEAP
char* _Need_free ChrHexToDec(const char* hex);
char* ChrDecToHex(char* dec);// Output: upper case
char* _Need_free ChrHexToDecFloat(const char* hexf);
char* _Need_free ChrDecToHexFloat(const char* decf, size_t digits);
char* ChrAdd(const char* dest, const char* sors);
char* ChrSub(const char* dest, const char* sors);
char* ChrMul(const char* a, const char* b);
void ChrDiv(char* a, char* b);// return a as Quotient, b as remainder.
char* ChrFactorial(const char* a);// a has prefix '+'
char* ChrArrange(const char* total, const char* items);
char* ChrCombinate(const char* total, const char* items);
char* ChrComDiv(const char* op1, const char* op2);// [Get Greatest Common Divisor]
char* ChrComMul(const char* op1, const char* op2);// [Get Least Common Multiple]

#endif
#ifdef _LIB_STRING_BUFFER
char* _Need_free ChrHexToDecBuf(const char* hex);
char* ChrDecToHexBuf(char* dec);// Output: upper case
char* ChrAddBuf(const char* dest, const char* sors);
char* ChrSubBuf(const char* dest, const char* sors);
char* ChrMulBuf(const char* a, const char* b);
void ChrDivBuf(char* a, char* b);// return a as Quotient, b as remainder.
char* ChrFactorialBuf(const char* a);// a has prefix '+'
char* ChrArrangeBuf(const char* total, const char* items);
char* ChrCombinateBuf(const char* total, const char* items);
char* ChrComDivBuf(const char* op1, const char* op2);// [Get Greatest Common Divisor]
char* ChrComMulBuf(const char* op1, const char* op2);// [Get Least Common Multiple]

#endif

int ChrCmp(const char* a, const char* b);// -1 0 1

void DigInc(int ascii, char* posi);
void DigDec(int ascii, char* posi);


static inline char* _Need_free ChrFromByt(unsigned char* str, size_t bylen)
{
	// started from RedToLocaleClassic()
	// 9876_5432H <=== 0x32,0x54,0x76,0x98;
	// 9876.5432H <=== 0x32,0x54`0x76,0x98;
	register char* res = malc((bylen << 1) | 1);
	char c;
	res += (bylen << 1);
	*res-- = 0;
	for (size_t i = 0; i < bylen; i++)
	{
		c = str[i] & 0x0F;
		*res-- = c >= 10 ? c - 10 + 'A' : c + '0';
		str[i] >>= 4;
		c = str[i] & 0x0F;
		*res-- = c >= 10 ? c - 10 + 'A' : c + '0';
	}
	return res + 1;
}

static inline unsigned char* _Need_free ChrToByt(char* str)
{
	// 98765432H ===> 0x32,0x54,0x76,0x98;
	// keep the str even, so you may allocate an odd size.
	// Without input check
	size_t slen = StrLength(str);
	if (slen & 1) return 0;
	slen >>= 1;
	unsigned char CrtChr = 0, * res = malc(slen + 1);
	res[slen] = 0;
	size_t i = slen;
	do
	{
		CrtChr = 0;
		if (str[1] >= 'A') CrtChr = str[1] - 'A';
		else CrtChr = str[1] - '0';
		if (str[0] >= 'A') CrtChr |= (str[0] - 'A') << 4;
		else CrtChr |= (str[0] - '0') << 4;
		str += 2;
		i--;
		res[i] = CrtChr;
	} while (i > 0);
	return res;
}

//
// Temporarily Stage Area
//

// Boundary
static inline unsigned char StrShiftLeft4(void* s, size_t len)
{
	unsigned char carry;
	unsigned char lastc = 0;
	do
	{
		carry = ((*(unsigned char*)s) & 0xF0) >> 4;// ArinaCove
		(*(unsigned char*)s) <<= 4;
		*(*((unsigned char**)&s))++ |= lastc;
		lastc = carry;
	} while (--len);
	return lastc;
}

// Boundary
static inline void StrShiftLeft8n(void* s, size_t len, size_t n)
{
	///MemRelative(s, len, (ptrdiff_t)n);
	register size_t i = 0;
	if (len == 0 || n == 0) return;
	if (n >= len) MemSet((unsigned char*)s, 0, len);
	else
	{
		while (i < len) { if (i + 1 > n) ((unsigned char*)s)[len + n - i - 1] = ((unsigned char*)s)[len - i - 1]; i++; }
		for (size_t j = 0; j < n; j++) ((unsigned char*)s)[j] = 0;
	}
	return;
}

// Boundary
static inline unsigned char StrShiftRight4(void* s, size_t len)
{
	unsigned char carry;
	unsigned char lastc = 0;
	*(char**)s += len - 1;
	do
	{
		carry = ((*(unsigned char*)s) & 0x0F) << 4;// ArinaCove
		(*(unsigned char*)s) >>= 4;
		*(*((unsigned char**)&s))-- |= lastc;
		lastc = carry;
	} while (--len);
	return lastc;
}

// Boundary, may renamed StrShiftRightBytes
static inline void StrShiftRight8n(void* s, size_t len, size_t n)
{
	///MemRelative(s, len, -(ptrdiff_t)n);
	register size_t i = 0;
	if (len == 0 || n == 0) return;
	if (n >= len) MemSet(s, 0, len);
	else
	{
		while (i < len) { if (i >= n) *(((unsigned char*)s) + i - n) = ((unsigned char*)s)[i]; i++; }
		for (size_t j = 0; j < n; j++) (((unsigned char*)s) - n + len)[j] = 0;
	}
}

static inline signed MemCompareRight(const unsigned char* a, const unsigned char* b, size_t n)
{
	for (ptrdiff_t i = n - 1; i >= 0; i--)
	{
		int state = (unsigned int)a[i] - (unsigned int)b[i];
		if (state) return state;
	}
	return 0;
}

#endif

// IN MEMORY OF OUR PAST YEARS //
