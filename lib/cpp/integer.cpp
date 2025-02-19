// ASCII C++-11 TAB4 CRLF
// Attribute: <ArnCovenant> <Env> <bin^%> <CPU()> [Allocation]
// LastCheck: 20240409
// AllAuthor: @dosconio
// ModuTitle: Integer based on ChrA/Br
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


#include "../../inc/cpp/integer"
#include "../../inc/cpp/string"

namespace uni {
	template<> String Integer_T<int32>::ToString() {
		String str;
		str.Format("%d", val);
		return str;
	}
}
