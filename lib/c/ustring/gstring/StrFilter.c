// ASCII C99 TAB4 CRLF
// Attribute: ArnCovenant 
// LastCheck: RFZ22
// AllAuthor: @dosconio
// ModuTitle: Operations for ASCIZ Character-based String
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

#include "../../../../inc/c/ustring.h"
#if !defined(_MCCA)
#include <ctype.h>// na isXType()

void StrFilter(char* p, toktype tt)
{
	char* q = p;
	char c;
	int (*jdg)(int);
	switch (tt)
	{
	case tok_spaces: jdg = isspace; break;
	case tok_number: jdg = isdigit; break;
	// ...
	default: return;
	}
	for (; (c = *p) != 0; p++)
		if (jdg(c))
			*q++ = c;
	*q = 0;
}
#endif
