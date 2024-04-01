// ASCII C++ TAB4 CRLF
// Attribute: <ArnCovenant> <Env> <bin^%> <CPU()> [Allocation]
// LastCheck: <date>
// AllAuthor: ...
// ModuTitle: ...
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

#include "../../inc/cpp/coear"
#include "math.h"

namespace uni{
	Coe::~Coe() {
		CoeDel(this->co);
	}
	Coe::Coe(const char* coff, const char* divr, const char* expo, stduint dimension) {
		CoeInit();
		co = CoeNew(coff, expo, divr);
		co->symb = dimension;
	}
	Coe::Coe(double num) {
		CoeInit();
		co = CoeFromDouble(num);
	}
	Coe::Coe(const char* local_str) {
		CoeInit();
		co = CoeFromLocale(local_str);
	}
	Coe::Coe(const Coe& c) {
		CoeInit();
		co = CoeCpy(c.co);
	}
	Coe::Coe(coe* c) : co(c) { CoeInit(); }

	void Coe::Srs(const Coe& c) {
		if (co) CoeDel(co);
		co = CoeCpy(c.co);
	}

	Coe Coe::pi() { return Coe(CoePi()); }
	Coe Coe::e() { return Coe(CoeE()); }

	double Coe::GetReal() const { return CoeToDouble(co); }

	std::string Coe::ToString(int opt) const {
		char* str = CoeToLocale(co, opt);
		std::string s = str;
		memfree(str);
		return s;
	}

	Coe::operator double() const { return CoeToDouble(this->co); }

	Coe& operator++ (Coe& num) {// prefix
		CoeAdd(num.co, &coeone);
		return num;
	}

	Coe Coe::operator++ (int) {// suffix, do not pass Reference&
		// Coe* prev = new Coe (*this);
		//-What is the principle? Haruno saw the return is called by twice before return then destructure.
		Coe prev = *this;
		CoeAdd(this->co, &coeone);
		return prev;
	}

	Coe& operator-- (Coe& num) {// prefix
		// based on above
		CoeSub(num.co, &coeone);
		return num;
	}

	Coe Coe::operator-- (int) {// suffix, do not pass Reference&
		// based on above
		Coe prev = *this;
		CoeSub(this->co, &coeone);
		return prev;
	}

	Coe Coe::operator+ () const {
		return *this;
	}

	Coe Coe::operator+ (Coe& s1) {
		Coe res(CoeCpy(this->co));
		CoeAdd(res.co, s1.co);
		return res;
	}

	Coe operator+ (const Coe& s0, const double s1) {
		Coe ret(CoeCpy(s0.co));
		Coe res1(CoeFromDouble(s1));
		CoeAdd(ret.co, res1.co);
		return ret;
	}
	Coe operator+ (const double s1, const Coe& s0) {
		return s0 + s1;
	}

	Coe& Coe::operator+= (const Coe& src) {
		CoeAdd(this->co, src.co);
		return *this;
	}

	Coe Coe::operator- () {
		Coe ret(CoeCpy(this->co));
		CoeNeg(ret.co);
		return ret;
	}

	Coe Coe::operator- (Coe& s1) {
		Coe res(CoeCpy(this->co));
		CoeSub(res.co, s1.co);
		return res;
	}

	Coe operator- (const Coe& s0, const double s1) {
		Coe ret(CoeCpy(s0.co));
		Coe res1(CoeFromDouble(s1));
		CoeSub(ret.co, res1.co);
		return ret;
	}

	Coe operator- (const double s1, const Coe& s0) {
		Coe res0(CoeCpy(s0.co));
		Coe res1(CoeFromDouble(s1));
		CoeSub(res1.co, res0.co);
		return res1;
	}

	Coe& Coe::operator-= (const Coe& src) {
		CoeSub(this->co, src.co);
		return *this;
	}

	Coe Coe::operator* (Coe& s1) {
		Coe res(CoeCpy(this->co));
		CoeMul(res.co, s1.co);
		return res;
	}

	Coe operator* (const Coe& s0, const double s1) {
		Coe ret(CoeCpy(s0.co));
		Coe res1(CoeFromDouble(s1));
		CoeMul(ret.co, res1.co);
		return ret;
	}
	Coe operator* (const double s1, const Coe& s0) { return s0 * s1; }

	Coe Coe::operator/ (Coe& s1) {
		Coe res(CoeCpy(this->co));
		CoeDiv(res.co, s1.co);
		return res;
	}

	Coe& Coe::operator*= (const Coe& src) {
		CoeMul(this->co, src.co);
		return *this;
	}

	Coe operator/ (const Coe& s0, const double s1) {
		Coe res0(CoeCpy(s0.co));
		Coe res1(CoeFromDouble(s1));
		CoeDiv(res0.co, res1.co);
		return res0;
	}

	Coe operator/ (const double s1, const Coe& s0) {
		Coe res0(CoeCpy(s0.co));
		Coe res1(CoeFromDouble(s1));
		CoeDiv(res1.co, res0.co);
		return res1;
	}

	Coe& Coe::operator/= (const Coe& src) {
		CoeDiv(this->co, src.co);
		return *this;
	}

	std::ostream& operator<< (std::ostream& out, const uni::Coe& c) {
		char* tofree = CoeToLocale(c.co, 0);
		if (tofree) out << tofree;
		mfree(tofree);
		return out;
	}

	Coe operator^ (const uni::Coe& b, const uni::Coe& c) {
		double tofree_des = CoeToDouble(b.co);
		double tofree_src = CoeToDouble(c.co);
		Coe ret(CoeFromDouble(pow(tofree_des, tofree_src)));
		return ret;
	}

	Coe& Coe::operator^= (const Coe& src) {
		Srs(CoeFromDouble(pow(operator double(), double(src))));
		return *this;
	}

}



