// ASCII CPP TAB4 CRLF
// Docutitle: (Driver) SRAM
// Codifiers: @dosconio: 20240723
// Attribute: Arn-Covenant Any-Architect Bit-32mode Non-Dependence
// Copyright: UNISYM, under Apache License 2.0; Dosconio Mecocoa, BSD 3-Clause License
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

#ifndef _INC_SRAM
#define _INC_SRAM
#include "../../cpp/unisym"
#include "../../cpp/reference"
#if defined(_MCU_STM32F1x)

namespace uni {

	class SRAM_t {
	private:
	public:
		
	};
}

#endif

#ifdef _MPU_STM32MP13
namespace uni {

	// AHB5
	// Backup SRAM
	class BKPSRAM_t {
	private:
	public:
		//
		stduint getAddress() const;
		// AKA __HAL_RCC_BKPSRAM_CLK_ENABLE
		void enClock(bool ena = true) const;
	};
	extern BKPSRAM_t BKPSRAM;
}
#endif

#endif
