// ASCII
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

#ifndef _LIB_DATETIME
#define _LIB_DATETIME

#include "alice.h"

// origin: unisym/kasha/n_timer.a : %imacro GetMoexDayIdentity 2
// year>=2014, month>0
// Return pastdays and weekday(0~6)
unsigned GetMoexDayIdentity(word year, word month, byte* weekday, byte* moondays);

#define isLeapYear(year) (!((year)&3)&&((year)%100)||!((year)%400)) // RFQ27


#endif
