// ASCII CPP TAB4 CRLF
// Docutitle: (Device) General Purpose Input Output
// Codifiers: @dosconio: 20240412
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
#include "../../../inc/cpp/Device/GPIO"
#include "../../../inc/cpp/Device/RCC/RCC"
#include "../../../inc/cpp/Device/RCC/RCCAddress"
#include "../../../inc/c/binary.h"

namespace uni
{

#if defined(_MCU_STM32F10x) || defined(_MCU_STM32F4x)

	static Request_t GPIO_Request_list[16] = {
		IRQ_EXTI0, IRQ_EXTI1, IRQ_EXTI2, IRQ_EXTI3,
		IRQ_EXTI4, IRQ_EXTI9_5, IRQ_EXTI9_5, IRQ_EXTI9_5,
		IRQ_EXTI9_5, IRQ_EXTI9_5, IRQ_EXTI15_10, IRQ_EXTI15_10,
		IRQ_EXTI15_10, IRQ_EXTI15_10, IRQ_EXTI15_10, IRQ_EXTI15_10
	};

	void GeneralPurposeInputOutputPin::setInterrupt(Handler_t fn) {
		FUNC_EXTI[bitposi] = fn;
	}


	void GeneralPurposeInputOutputPin::setInterruptPriority(byte preempt, byte sub_priority) {
		NVIC.setPriority(GPIO_Request_list[bitposi], preempt, sub_priority);
	}

	//{TODO}
	void GeneralPurposeInputOutputPin::enInterrupt(bool enable) {
		NVIC.setAble(GPIO_Request_list[bitposi], enable);
	}

	void GeneralPurposeInputOutputPin::setMode(GPIORupt::RuptEdge edg) {
		if (!isInput())
			setMode(GPIOMode::IN_Floating);

		#if defined(_MCU_STM32F10x)
		RCC.APB2.enAble(_RCC_APB2ENR_POSI_ENCLK_AFIO_BITPOS);

		#elif defined(_MCU_STM32F4x)
		RCC.APB2.enAble(14);// SYSCFG EN
		
		#endif
		for0(i, 10);// some delay to wait, magic_num: random
		Reference& CrtEXTICR = AFIO::ExternInterruptCfgs[bitposi >> 2];
		byte CrtPosi = (bitposi & 0x3) * 4;
		CrtEXTICR = (CrtEXTICR &
			~(stduint)(0xF << CrtPosi)) |
			(GPIO.Index(parent) << CrtPosi);
		EXTI::TriggerRising.setof(bitposi, edg != GPIORupt::Negedge);
		EXTI::TriggerFalling.setof(bitposi, edg != GPIORupt::Posedge);
		EXTI::MaskInterrupt.setof(bitposi); // Mask EVENT/INTERRUPT, //{TODO}while GPIOEvent Set MaskEvent, the above are same
	}

#endif

#ifdef _MCU_STM32F10x

	#define _OFFSET_GPIO_CRL 0x00
	#define _OFFSET_GPIO_CRH 0x04
	#define _OFFSET_GPIO_IDR 0x08
	#define _OFFSET_GPIO_ODR 0x0C

	GeneralPurposeInputOutputPort::GeneralPurposeInputOutputPort(uint32 ADDR, uint32 CLK, uint32 Enap) :
		EnablPosi(Enap), // (RCC_APB2ENR)
		ClockPort(CLK), // Enable Clock
		CnrglPort(_OFFSET_GPIO_CRL + ADDR),
		CnrghPort(_OFFSET_GPIO_CRH + ADDR),
		InnpdPort(_OFFSET_GPIO_IDR + ADDR),
		OutpdPort(_OFFSET_GPIO_ODR + ADDR),
		base(ADDR)
	{
		for0(i, numsof(OutpdPins))
			OutpdPins[i] = GeneralPurposeInputOutputPin(this, i);
	}

	GeneralPurposeInputOutputPort GPIOA(0x40010800, _RCC_APB2ENR_ADDR, _RCC_APB2ENR_POSI_ENCLK_GPIOA);
	GeneralPurposeInputOutputPort GPIOB(0x40010C00, _RCC_APB2ENR_ADDR, _RCC_APB2ENR_POSI_ENCLK_GPIOB);
	GeneralPurposeInputOutputPort GPIOC(0x40011000, _RCC_APB2ENR_ADDR, _RCC_APB2ENR_POSI_ENCLK_GPIOC);
	GeneralPurposeInputOutputPort GPIOD(0x40011400, _RCC_APB2ENR_ADDR, _RCC_APB2ENR_POSI_ENCLK_GPIOD);
	GeneralPurposeInputOutputPort GPIOE(0x40011800, _RCC_APB2ENR_ADDR, _RCC_APB2ENR_POSI_ENCLK_GPIOE);
	GeneralPurposeInputOutputPort GPIOF(0x40011C00, _RCC_APB2ENR_ADDR, _RCC_APB2ENR_POSI_ENCLK_GPIOF);
	GeneralPurposeInputOutputPort GPIOG(0x40012000, _RCC_APB2ENR_ADDR, _RCC_APB2ENR_POSI_ENCLK_GPIOG);

	static GeneralPurposeInputOutputPort* GPIO_List[] = {
	&GPIOA, &GPIOB, &GPIOC, &GPIOD, &GPIOE, &GPIOF, &GPIOG
	};

#if 1
	
	GeneralPurposeInputOutputPin::operator bool() const {
		return (innput ? parent->InnpdPort : parent->OutpdPort) & (1 << bitposi);
	}

	bool GeneralPurposeInputOutputPin::getInn() {
		return parent->InnpdPort & (1 << bitposi);
	}
	
	GeneralPurposeInputOutputPin& GeneralPurposeInputOutputPin::operator=(bool val) {
		// if (innput) return *this;
		// G'DP or D'DP
		if (val)
			BitSet(parent->OutpdPort, bitposi);
		else
			BitClr(parent->OutpdPort, bitposi);
		return *this;
	}

	void GeneralPurposeInputOutputPin::setMode(GPIOMode::Mode mode, GPIOSpeed::Speed speed, bool autoEnClk) {
		if (autoEnClk) parent->enClock();
		Reference& ref = (bitposi < 8) ? parent->CnrglPort : parent->CnrghPort;
		uint32 bposi = (bitposi < 8) ? bitposi << 2 : (bitposi - 8) << 2; // mul by 4
		uint32 bmode = (uint32)mode;
		innput = (bmode & 1);
		uint32 state = innput ? GPIOSpeed::Atmost_Input : speed;
		state |= (bmode & 0xC);// 0b1100
		ref = (ref & ~(0xf << bposi)) | (state << bposi);// or treat it a double-length Reference (64-bit)
	}


	// for F1, only for input (?)
	void GeneralPurposeInputOutputPin::setPull(bool pullup) {
		(parent->OutpdPort).setof(bitposi, pullup);
	}

	bool GeneralPurposeInputOutputPin::isInput() const {
		return 0 == (uint32_t(bitposi < 8 ? parent->CnrglPort : parent->CnrghPort) &
			(0x3 << ((bitposi & 0x7)*4)));
	}
	
	void GeneralPurposeInputOutputPin::Toggle() {
		parent->OutpdPort ^= 1 << bitposi;
	}

	GeneralPurposeInputOutputPort::operator stduint() const {
		return (stduint)InnpdPort;
	}

	//{unchecked}
	void Lock(bool tolock_orunlock) {
		//{TODO}
	}
#endif
// ---- ---- ---- ----
#elif defined(_MCU_STM32F4x)

	//{TODEL}
	#define _OFFSET_GPIO_MODER 0x00
	#define _OFFSET_GPIO_OTYPE 0x04
	#define _OFFSET_GPIO_SPEED 0x08
	#define _OFFSET_GPIO_PULLS 0x0C
	#define _OFFSET_GPIO_IDR   0x10
	#define _OFFSET_GPIO_ODR   0x14

	GeneralPurposeInputOutputPort::GeneralPurposeInputOutputPort(uint32 ADDR, uint32 CLK, uint32 Enap) :
		baseaddr(ADDR),
		EnablPosi(Enap), // (RCC_APB2ENR)
		ClockPort(CLK), // Enable Clock
		InnpdPort(_OFFSET_GPIO_IDR + ADDR),
		OutpdPort(_OFFSET_GPIO_ODR + ADDR),
		//
		ModerPort(_OFFSET_GPIO_MODER + ADDR),
		OtypePort(_OFFSET_GPIO_OTYPE + ADDR),
		SpeedPort(_OFFSET_GPIO_SPEED + ADDR),
		PullsPort(_OFFSET_GPIO_PULLS + ADDR)
		//{TODO...} base(ADDR),
		
	{
		for0(i, numsof(OutpdPins))
			OutpdPins[i] = GeneralPurposeInputOutputPin(this, i);
	}

	GeneralPurposeInputOutputPort GPIOA(0x40020000, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOA);// ~ 0x400203FF
	GeneralPurposeInputOutputPort GPIOB(0x40020400, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOB);
	GeneralPurposeInputOutputPort GPIOC(0x40020800, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOC);
	GeneralPurposeInputOutputPort GPIOD(0x40020C00, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOD);//
	GeneralPurposeInputOutputPort GPIOE(0x40021000, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOE);
	GeneralPurposeInputOutputPort GPIOF(0x40021400, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOF);
	GeneralPurposeInputOutputPort GPIOG(0x40021800, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOG);
	GeneralPurposeInputOutputPort GPIOH(0x40021C00, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOH);
	GeneralPurposeInputOutputPort GPIOI(0x40022000, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOI);
	// GeneralPurposeInputOutputPort GPIOJ(0x40022400, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOJ);
	// GeneralPurposeInputOutputPort GPIOK(0x40022800, _RCC_AHB1ENR_ADDR, _RCC_AHB1ENR_POSI_ENCLK_GPIOK);

	static GeneralPurposeInputOutputPort* GPIO_List[] = {
		&GPIOA, &GPIOB, &GPIOC, &GPIOD, &GPIOE, &GPIOF, &GPIOG, &GPIOH, &GPIOI
	};

	GeneralPurposeInputOutputPin::operator bool() const {
		return (innput ? parent->InnpdPort : parent->OutpdPort) & (1 << bitposi);
	}

	GeneralPurposeInputOutputPin& GeneralPurposeInputOutputPin::operator=(bool val) {
		// if (innput) return *this;
		// G'DP or D'DP
		//{TO update}
		if (val)
			BitSet(parent->OutpdPort, bitposi);
		else
			BitClr(parent->OutpdPort, bitposi);
		return *this;
	}

	void GeneralPurposeInputOutputPin::setMode(GPIOMode::Mode mode, GPIOSpeed::Speed speed, bool autoEnClk) {
		if (autoEnClk) parent->enClock();
		parent->ModerPort &= ~(uint32)(0x3 << (bitposi << 1));
		parent->ModerPort |= (((stduint)mode)>>1) << (bitposi << 1);
		if ((stduint)mode & 1)
			BitSet(parent->OtypePort, bitposi);
		else
			BitClr(parent->OtypePort, bitposi);
		parent->SpeedPort &= ~(uint32)(0x3 << (bitposi << 1));
		parent->SpeedPort |= (stduint)speed << (bitposi << 1);
		if (mode == GPIOMode::IN_Floating) parent->PullsPort &= ~(uint32)(0x3 << (bitposi << 1));
		innput = (GPIOMode::IN_Floating == mode) || (GPIOMode::IN_Analog == mode) || (GPIOMode::IN_Pull == mode); // KEPT
		
	}

	void GeneralPurposeInputOutputPin::setPull(bool pullup) {
		if (pullup) {
			parent->PullsPort |= 0x1 << (bitposi << 1);// pull-up
			parent->PullsPort &= ~(uint32)(0x2 << (bitposi << 1));
		}
		else {
			parent->PullsPort |= 0x2 << (bitposi << 1);// pull-dn
			parent->PullsPort &= ~(uint32)(0x1 << (bitposi << 1));
		}
	}

	bool GeneralPurposeInputOutputPin::isInput() const {
		return 0 == (parent->ModerPort &
			(0x3 << ((bitposi & 0xF) * 2)));
	}

	void GeneralPurposeInputOutputPin::Toggle() {
		parent->OutpdPort ^= 1 << bitposi;
	}

	void GeneralPurposeInputOutputPin::_set_alternate(byte selection) {
		selection &= 0xF;
		byte bposi = (bitposi & 0x7) << 2;// mod 8 then mul-by 4
		Reference r = parent->operator[](bitposi < 8 ? GPIOReg::AFRL : GPIOReg::AFRH);
		r = (r & ~(stduint)(0xF << bposi)) | (selection << bposi);
	}

	bool GeneralPurposeInputOutputPin::getInn() {
		return getParent()[GPIOReg::IDR].bitof(bitposi);
	}

	GeneralPurposeInputOutputPort::operator stduint() const {
		return (stduint)InnpdPort;
	}

// ---- ---- ---- ----
#elif defined(_MCU_CW32F030)

	GeneralPurposeInputOutputPort GPIOA(0x48000000, _SYSC_AHBEN_ADDR, _SYSC_AHBEN_POS_GPIOA);
	GeneralPurposeInputOutputPort GPIOB(0x48000400, _SYSC_AHBEN_ADDR, _SYSC_AHBEN_POS_GPIOB);
	GeneralPurposeInputOutputPort GPIOC(0x48000800, _SYSC_AHBEN_ADDR, _SYSC_AHBEN_POS_GPIOC);
	GeneralPurposeInputOutputPort GPIOF(0x48001400, _SYSC_AHBEN_ADDR, _SYSC_AHBEN_POS_GPIOF);

	static GeneralPurposeInputOutputPort* GPIO_List[] = {
		&GPIOA, &GPIOB, &GPIOC, 0, 0, &GPIOF
	};

	void GeneralPurposeInputOutputPin::setMode(GPIOMode::Mode mod, GPIOSpeed::Speed spd, bool autoEnClk) {
		using namespace GPIOReg;
		const stduint mode = mod;
		GeneralPurposeInputOutputPort& pare = getParent();
		if (autoEnClk) pare.enClock();
		pare.getReference(DIR).setof(bitposi, mode & 0x1);
		pare.getReference(OPENDRAIN).setof(bitposi, mode & 0x2);
		pare.getReference(SPEED).setof(bitposi, 0 != (stduint)spd);
		pare.getReference(ANALOG).setof(bitposi, 0);/*TEMP*/
		innput = mode & 0x1;
	}
	
	void GeneralPurposeInputOutputPin::Toggle() {
		using namespace GPIOReg;
		GeneralPurposeInputOutputPort& pare = getParent();
		pare.getReference(TOG).setof(bitposi);
	}

	GeneralPurposeInputOutputPin& GeneralPurposeInputOutputPin::operator= (bool val) {
		// if (innput) return self;
		getParent().getReference(GPIOReg::ODR).setof(bitposi, val);
		return self;
	}
	GeneralPurposeInputOutputPin::operator bool() const {
		if (innput) return getParent().getReference(GPIOReg::IDR).bitof(bitposi);
		return getParent().getReference(GPIOReg::ODR).bitof(bitposi);
	}
	bool GeneralPurposeInputOutputPin::getInn() {
		return getParent().getReference(GPIOReg::IDR).bitof(bitposi);
	}

	void GeneralPurposeInputOutputPin::setPull(bool dir) {
		using namespace GPIOReg;
		GeneralPurposeInputOutputPort& pare = getParent();
		pare.getReference(PUR).setof(bitposi, dir);
		pare.getReference(PDR).setof(bitposi, !dir);
	}

	GeneralPurposeInputOutputPort::operator stduint() const {
		return (stduint)getReference(GPIOReg::IDR);
	}

#endif

	GeneralPurposeInputOutput GPIO;
	
	GeneralPurposeInputOutputPort& GeneralPurposeInputOutputPin::getParent() const { return *parent; }
	
	GeneralPurposeInputOutputPort& GeneralPurposeInputOutput::operator[](char portid) {
		return ascii_isupper(portid) ? *(GPIO_List[
		#ifdef _MCU_MSP432
			portid
		#else
			portid - 'A'
		#endif
		]) : ERR;
	}

	stduint GeneralPurposeInputOutput::Index(const GeneralPurposeInputOutputPort* port) {
		for0 (i, numsof(GPIO_List)) {
			if (port == GPIO_List[i]) return i;
		}
		return 0;
	}

	//
	GeneralPurposeInputOutputPort& GeneralPurposeInputOutputPort::operator= (uint32 val) {
		#ifdef _MCU_STM32
		OutpdPort = val;
		#else
		using namespace GPIOReg;
		getReference(ODR) = val;
		#endif
		return *this;
	}

	GeneralPurposeInputOutputPin& GeneralPurposeInputOutputPort::operator[] (byte pinid) {
		#ifdef _MCU_STM32
		return pinid < numsof(OutpdPins) ? OutpdPins[pinid] : ERR;
		#elif defined(_MCU_CW32F030)
		return pinid < numsof(pins) ? pins[pinid] : ERR;
		#endif
	}
	
	GeneralPurposeInputOutputPin& GeneralPurposeInputOutputPin::operator=(const GeneralPurposeInputOutputPin& pin) {
		if (!parent) { // Initialize
			parent = pin.parent; bitposi = pin.bitposi; innput = pin.innput;
			return self;
		}
		else return self = bool(pin); // Assign 
	}

	// This will not be for declaration expression
	GeneralPurposeInputOutputPort& GeneralPurposeInputOutputPort::operator= (const GeneralPurposeInputOutputPort& pot) {
		return self = stduint(pot);
	}
}

