// ASCII CPL TAB4 CRLF
// Docutitle: AT24C02
// Datecheck: 20240429 ~ <Last-check>
// Developer: @dosconio
// Attribute: Arn-Covenant Any-Architect Env-Freestanding Non-Dependence
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

#include "../../../../inc/c/stdinc.h"
#include "../../../../inc/c/driver/AT24C02.h"

#if defined(_MCU_Intel8051) && defined(_AT24C02_ADDRESS)

void AT24C02_SetByte(unsigned char WordAddress, unsigned char Data)
{
	I2C_Start();
	I2C_SetByte(_AT24C02_ADDRESS);
	I2C_GetAck();
	I2C_SetByte(WordAddress);
	I2C_GetAck();
	I2C_SetByte(Data);
	I2C_GetAck();
	I2C_Stop();
}

unsigned char AT24C02_GetByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SetByte(_AT24C02_ADDRESS);
	I2C_GetAck();
	I2C_SetByte(WordAddress);
	I2C_GetAck();
	I2C_Start();
	I2C_SetByte(_AT24C02_ADDRESS | 0x01);
	I2C_GetAck();
	Data = I2C_GetByte();
	I2C_SetAck(1);
	I2C_Stop();
	return Data;
}

#endif
