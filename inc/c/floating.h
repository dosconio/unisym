// ASCII CPL TAB4 CRLF
// Docutitle: Floating
// Datecheck: 20240421 ~ <Last-check>
// Developer: @dosconio
// Attribute: <ArnCovenant> <Environment> <Platform>
// Reference: <Reference>
// Dependens: <Dependence>
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

//{Option} {TODO!} software implementation or hardware implementation (by instruction by driving Co-processor)

// Compatible with:
//{TODO} - ISO limits.h
//{TODO} - ISO float.h
//{TODO} - ISO fenv.h


#ifndef _INC_FLOATING
#define _INC_FLOATING

#include "integer.h"

#define isZeroMantissa(flt) ((int)(flt)==(flt)) 
#define getNearInteger(flt) (flt+0.5)

#endif
