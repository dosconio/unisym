// UTF-8 CPP-ISO11 TAB4 CRLF
// Docutitle: (Device) Double Data Rate (DDR) Memory
// Codifiers: @dosconio: 20241213 ~ <Last-check> 
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

#include "../../../../inc/cpp/Device/DDR"
#include "../../../../inc/cpp/MCU/_ADDRESS/ADDR-STM32.h"

namespace uni {
#ifdef _MPU_STM32MP13
	DDR_t DDR;

	Reference DDR_t::operator[](DDRControl idx) const {
		return APB4_PERIPH_BASE + 0x3000 + _IMMx4(idx);
	}
	Reference DDR_t::operator[](DDRPerform idx) const {
		return APB4_PERIPH_BASE + 0x7000 + _IMMx4(idx);
	}
	Reference DDR_t::operator[](DDRPhyziks idx) const {
		return APB4_PERIPH_BASE + 0x4000 + _IMMx4(idx);
	}

	bool DDR_t::setMode(bool wakeup_from_standby, bool self_refresh, stduint zdata, bool clear_bkp) const {


		return true;
	}


#endif
}

