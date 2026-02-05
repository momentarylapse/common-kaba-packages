#include <stdlib.h>
#include <stdio.h>
#include "../base/base.h"
#include "algebra.h"
#include "../math/math.h"

using uint64 = unsigned long long;

//#define vlidb(m)	msg_write((m));
#define vlidb(m)


#if defined(OS_LINUX) && (defined(CPU_AMD64) || defined(CPU_X86))
	#define ALLOW_ASM 1
#elif defined(OS_WINDOWS) && defined(CPU_X86)
	#define ALLOW_ASM 1
#endif

//#if ALLOW_ASM

inline void _mul_(unsigned int &a, unsigned int b, unsigned int &oh) {
#if ALLOW_ASM
#ifdef OS_WINDOWS
	__asm{
		mov eax, b
		mul a
		mov a, eax
		mov oh, edx
	}
#else
	asm volatile(	"mov %2, %%eax\n\t"
		"mul %3\n\t"
		"mov %%eax, %0\n\t"
		"mov %%edx, %1"
		: "=r" (a), "=r" (oh)
		: "r" (a), "r" (b)
		: "%eax", "%edx");
#endif
#else
	uint64 i = a;
	i *= b;
	oh = i >> 32;
	a = i;
#endif
}


inline void _div_(unsigned int &a_l, unsigned int a_h, unsigned int b, unsigned int &orem) {
#if ALLOW_ASM
#ifdef OS_WINDOWS
	__asm{
		mov eax, a_l
		mov edx, a_h
		div b
		mov a_l, eax
		mov orem, edx
	}
#else
	asm volatile(	"mov %2, %%eax\n\t"
		"mov %3, %%edx\n\t"
		"div %4, %%eax\n\t"
		"mov %%eax, %0\n\t"
		"mov %%edx, %1"
		: "=r" (a_l), "=r" (orem)
		: "r" (a_l), "r" (a_h), "r" (b)
		: "%eax", "%edx");
#endif
#else
	uint64 i = a_l;
	i += ((uint64)a_h) << 32;
	orem = (i % (uint64)b);
	a_l = (i / (uint64)b);
#endif
}

inline void _add_(unsigned int &a, unsigned int b, bool &carry) {
#if ALLOW_ASM
#ifdef OS_WINDOWS
	if (carry)
		__asm stc
	else
		__asm clc
	bool _carry;
	__asm{
		mov eax, a
		adc b, eax
		setc _carry
	}
	carry = _carry;
#else
	if (carry)
		asm volatile("stc");
	else
		asm volatile("clc");
	asm volatile(
		"adc %3, %0\n\t"
		"setc %1\n\t"
		: "+r" (a), "+r" (carry)
		: "r" (a), "r" (b), "r" (carry)
		: "%eax");
#endif
#else
	uint64 i = a;
	i += b;
	if (carry)
		i += 1;
	a = i;
	carry = (i & 0xffffffff00000000);
#endif
}

inline void _sub_(unsigned int &a, unsigned int b, bool &carry) {
#if ALLOW_ASM
#ifdef OS_WINDOWS
	if (carry)
		__asm stc
	else
		__asm clc
	bool _carry;
	__asm{
		mov eax, a
		sbb eax, b
		mov a, eax
		setc _carry
	}
	carry = _carry;
#else
	if (carry)
		asm volatile("stc");
	else
		asm volatile("clc");
	asm volatile(
		"mov %2, %%eax\n\t"
		"sbb %3, %%eax\n\t"
		"mov %%eax, %0\n\t"
		"setc %1"
		: "=r" (a), "=r" (carry)
		: "r" (a), "r" (b)
		: "%eax");
#endif
#else
	uint64 i = a;
	i -= b;
	if (carry)
		i -= 1;
	a = i;
	carry = (i & 0xffffffff00000000);
#endif
}


BigInt::BigInt() {
	data.add(0);
	sign = false;
}

BigInt::BigInt(const BigInt &v) {
	sign = v.sign;
	data = v.data;
}

BigInt::BigInt(int v) {
	if (v >= 0) {
		sign = false;
		data.add(v);
	} else {
		sign = true;
		data.add(-v);
	}
}

BigInt::BigInt(const string &str) {
	data.add(0);
	sign = false;
	int i0 = 0;
	if ((str.num > 0) and (str[0] == '-')) {
		sign = true;
		i0 = 1;
	}
	Array<unsigned int> ui;
	ui.resize(1);
	for (int i=i0;i<str.num;i++) {
		if (i > i0)
			*this *= 10;
		ui[0] = (str[i] - '0');
		add_abs(ui);
	}
}

BigInt::~BigInt() {
	data.clear();
}

void BigInt::shift_units(int n) {
	if (n > 0)
		if (data[data.num - 1] != 0) {
			//data.insert(data.begin(), n, 0);
			data.resize(data.num + n);
			for (int i=data.num-1;i>=n;i--)
				data[i] = data[i - n];
			for (int i=0;i<n;i++)
				data[i] = 0;
		}
}

void BigInt::add_abs(const Array<unsigned int> &_data)
{
	int nmin = min(data.num, _data.num);
	int nmax = max(data.num, _data.num);
	bool carry = false;

	// cheap trick... move additional digits from <d> to <this>...
	if (_data.num > data.num){
		data.resize(_data.num);
		for (int i=nmin;i<nmax;i++)
			data[i] = _data[i];
	}

	// add the digits both operands share
	for (int i=0;i<nmin;i++)
		_add_(data[i], _data[i], carry);

	// treat carry on digits only <this> has
	for (int i=nmin;i<data.num;i++)
		if (carry)
			_add_(data[i], 0, carry);
		else
			break;

	// still carry -> add one digit
	if (carry)
		data.add(1);
}

void BigInt::sub_abs(const Array<unsigned int> &_data)
{
	if (data.num < _data.num){
		printf("vli.sub_abs()...\n");
		//printf("###################################\nerror:  -=  \n%s\n<\n%s\n###################################\n", to_string().c_str(), v.to_string().c_str());
		exit(0);
	}
	bool carry = false;

	// sub the digits both operands share
	for (int i=0;i<_data.num;i++)
		_sub_(data[i], _data[i], carry);

	// treat carry on digits only <this> has
	for (int i=_data.num;i<data.num;i++)
		if (carry)
			_sub_(data[i], 0, carry);
		else
			break;

	normalize();
}

void BigInt::normalize()
{
	for (int i=data.num-1;i>=1;i--)
		if (data[i] == 0)
			data.pop();
		else
			break;
	if (data.back() == 0)
		sign = false;
}

void BigInt::operator +=(const BigInt &v)
{
	if (sign == v.sign){
		add_abs(v.data);
	}else{
		if (compare_abs(v) < 0){
			BigInt r = v;
			r.sub_abs(data);
			r.sign = !sign and (r.data.back() != 0);
			*this = r;
		}else{
			sub_abs(v.data);
		}
	}
}

void BigInt::operator -=(const BigInt &v)
{
	if (sign != v.sign){
		add_abs(v.data);
	}else{
		if (compare_abs(v) < 0){
			BigInt r = v;
			r.sub_abs(data);
			r.sign = !sign and (r.data.back() != 0);
			*this = r;
		}else{
			sub_abs(v.data);
		}

		// normalize
		if (sign)
			if (data.back() == 0)
				sign = false;
	}
}

void BigInt::mul_ui(unsigned int v)
{
	unsigned int oh = 0;
	for (int i=0;i<data.num;i++){
		unsigned int oh_last = oh;
		_mul_(data[i], v, oh);
		if (oh_last > 0){
			bool carry = false;
			_add_(data[i], oh_last, carry);
			if (carry)
				oh ++;
		}
	}
	if (oh > 0)
		data.add(oh);
}

BigInt BigInt::operator *(const BigInt &v) const
{
	BigInt r;
	for (int i=0;i<v.data.num;i++){
		BigInt t = *this;
		t.mul_ui(v.data[i]);
		if (i > 0)
			t.shift_units(i);
		r.add_abs(t.data);
	}
	r.sign = (sign != v.sign) and (r.data.back() != 0);
	return r;
}

void BigInt::div(unsigned int divisor, unsigned int &remainder) {
	unsigned int last_rem = 0;
	for (int i=data.num-1;i>=0;i--) {
		unsigned int rem;
		_div_(data[i], last_rem, divisor, rem);
		last_rem = rem;
		if ((data[i] == 0) and (i == data.num - 1) and (data.num > 1))
			data.resize(data.num - 1);
	}
	remainder = last_rem;
}

/*inline int get_heading_zeroes(unsigned int x)
{
	for (int i=0;i<32;i++){
		unsigned int mask = (0xffffffff << i);
		if ((x & mask) == 0)
			return 32 - i;
	}
	return 0;
}

inline unsigned int get_fair_uint(unsigned int il, unsigned int ih, int shift)
{
	if (shift >= 32)
		return (il << (shift - 32));
	if ((shift < 0) and (shift < 32))
		return (ih << shift) + (il >> (32 - shift));
	else if (shift == 0)
		return ih;
	else if (shift < 0){
		printf("aaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaa\n");
		return 0;
	}
}*/

unsigned int div_fair(unsigned int al, unsigned int ah, unsigned int bl, unsigned int bh)
{
	vlidb(format("df %08x %08x / %08x %08x", ah, al, bh, bl));
//	int shift = min(get_heading_zeroes(ah), get_heading_zeroes(bh) + 32);
//	printf("shift %d\n", shift);
//	unsigned int aa = get_fair_uint(al, ah, shift);
//	unsigned int bb = get_fair_uint(bl, bh, shift - 32);
//	printf("%08x   %08x\n", aa, bb);
//	printf("     %08x\n", aa / bb);
	//return aa / bb;
	//return aa / bb;
	/*unsigned int rrr;
	_div_(al, ah, bh, rrr);
	printf("=>  %08x\n", al);
	return al;*/
	double a = (double)al + (double)ah * 4294967296.0;
	double b = (double)bl + (double)bh * 4294967296.0;
	return (unsigned int)(a / b * 4294967296.0 + 0.4);
}

void BigInt::div(const BigInt &divisor, BigInt &remainder)
{
	vlidb("div " + dump() + " / " + divisor.dump());
	remainder = *this;
	unsigned int div_hi = divisor.data[divisor.data.num - 1];
	unsigned int div_lo = 0;
	if (divisor.data.num > 1)
		div_lo = divisor.data[divisor.data.num - 2];
//	printf("aaa\n");
	bool first_set = true;
	for (int i=data.num-1;i>=(int)divisor.data.num-1;i--){
		vlidb(format("# %d    ", i));
		[[maybe_unused]] unsigned int guess, guess2=0;
		if (i == (int)remainder.data.num - 1){
			guess  = div_fair(remainder.data[i], 0, div_lo, div_hi);
			//guess2 = div_fair(remainder.data[i], 0, div_lo, div_hi+1);
		}else{
			//printf("dddddd  %u   %u %u \n",guess, data[i], data[i + 1], div_hi);
			guess  = div_fair(remainder.data[i], remainder.data[i + 1], div_lo, div_hi);
			//guess2 = div_fair(remainder.data[i], remainder.data[i + 1], div_lo, div_hi);

			//_div_(guess, remainder.data[i + 1], div_hi, rrr);
			//_div_(guess2, remainder.data[i + 1], div_hi, rrr);
		}
		vlidb(format("guess %08x   (%08x)\n", guess, guess2));
		BigInt div_shift = divisor;
		div_shift.shift_units(i - divisor.data.num + 1);
		BigInt t = div_shift;
		guess ++;
		t.mul_ui(guess);
		vlidb("t = " + t.dump());
		vlidb("rem = " + remainder.dump());

		bool cont = false;
		while (t.compare_abs(remainder) > 0){
			vlidb("t >= rem");
			if (guess == 0){
				cont = true;
				break;
			}
			//printf("--\n");
			guess --;
			t.sub_abs(div_shift.data);
//			printf("t   = ");
//			t.printh();
//			printf("-\n");
		}
		if (cont)
			continue;
		remainder.sub_abs(t.data);
		vlidb("rem = " + remainder.dump());

		data[i - divisor.data.num + 1] = guess;
		if (first_set)
			data.resize(i - divisor.data.num + 2);
		/*if ((guess == 0) and (i == data.num - 1) and (i > 0))
			data.pop_back();*/
		first_set = false;
//		printf("div %d\n", divisor.data.num);
		//exit(0);
	}
	if ((data.back() == 0) and (data.num > 1))
		data.pop();
	sign = sign ^ divisor.sign;
//	printf("----------\n");
}

bool BigInt::operator == (const BigInt &v) const
{
	if (sign != v.sign)
		return false;
	if (data.num != v.data.num)
		return false;
	for (int i=0;i<data.num;i++)
		if (data[i] != v.data[i])
			return false;
	return true;
}

int BigInt::compare_abs(const BigInt &v) const
{
	//msg_write("cmp " + dump() + " == " + v.dump());
	if (data.num != v.data.num)
		return (data.num - v.data.num);
	for (int i=(int)data.num-1;i>=0;i--)
		if (data[i] != v.data[i]){
			if (data[i] > v.data[i])
				return 1;
			return -1;
		}
	return 0;
}

// < v => < 0
// > v => > 0
int BigInt::compare(const BigInt &v) const
{
	if (sign != v.sign)
		return (sign ? -1 : 1);
	if (sign)
		return -compare_abs(v);
	return compare_abs(v);
}

bool BigInt::operator < (const BigInt &v) const
{
	return (compare(v) < 0);
}

string BigInt::to_string() const
{
	BigInt t = *this;
	unsigned int rr;
	string s;
	while(true){
		t.div(1000000000, rr);
		for (int i=0;i<9;i++){
			div_t divresult = ::div(rr, 10);
			s.add('0' + divresult.rem);
			rr = divresult.quot;
			if ((t.data.num == 1) and (t.data[0] == 0) and (rr == 0))
				break;
		}
		if ((t.data.num == 1) and (t.data[0] == 0))
			break;
	}
	if (sign)
		s.add('-');
	return s.reverse();
}


void BigInt::operator = (const BigInt &v)
{
	data = v.data;
	sign = v.sign;
}

string BigInt::dump() const
{
	string s = format("%s%08x", (sign ? "-" : "+"), data.back());
	for (int i=data.num-2;i>=0;i--)
		s += format(".%08x", data[i]);
	return s;
}

BigInt BigInt::pow(const BigInt &x, const BigInt &e) {
	// number of bits in highest unit of exponent
	int nex = 0;
	for (int i=0;i<32;i++)
		if ((e.data.back() & (1 << i)) > 0)
			nex = i + 1;
	BigInt r = 1;
	BigInt t = x;
	for (int u=0;u<e.data.num;u++) {
		int nmax = (u == e.data.num - 1) ? nex : 32;
		for (int i=0;i<nmax;i++) {
			if ((e.data[u] & (1 << i)) > 0)
				r *= t;
			if ((i < nex - 1) or (u < e.data.num - 1))
				t *= t;
		}
	}
	r.sign = (x.sign and ((e.data[0] & 1) > 0));
	return r;
}

// r = ((base ^ e) % m)
BigInt BigInt::pow_mod(const BigInt &x, const BigInt &e, const BigInt &m) {
	// number of bits in highest unit of exponent
	int nex = 0;
	for (int i=0;i<32;i++)
		if ((e.data.back() & (1 << i)) > 0)
			nex = i + 1;


	BigInt r = 1;
	BigInt t;
	BigInt base2 = x;
	base2.div(m, t); // t = (base % m)
	for (int u=0;u<e.data.num;u++) {
		int nmax = (u == e.data.num - 1) ? nex : 32;
		for (int i=0;i<nmax;i++) {
			if ((e.data[u] & (1 << i)) > 0) {
				r *= t;
				BigInt rr;
				r.div(m, rr);
				r = rr;
			}
			if ((i < nex - 1) or (u < e.data.num - 1)) {
				t *= t;
				BigInt tt;
				t.div(m, tt);
				t = tt;
			}
		}
	}
	r.sign = x.sign;
	return r;
}

BigInt BigInt::gcd(const BigInt &_a, const BigInt &_b) {
	BigInt a = _a;
	BigInt b = _b;
	BigInt vli0 = 0;
	BigInt rem;
	while (b != vli0) {
		a.div(b, rem);
		a = b;
		b = rem;
	}
	a.sign = false;
	return a;
}



int BigInt::count_bits() const {
	int bits = 32 * (data.num - 1);
	for (int i=31;i>=0;i--)
		if ((data.back() & (1 << i)) != 0){
			bits += i;
			break;
		}
	return bits;
}

BigInt BigInt::rand(int bits) {
	BigInt v;
	v.data.resize((bits-1)/32 + 1);
	for (int i=0;i<v.data.num;i++)
		for (int j=0;j<4;j++)
			v.data[i] ^= randi(255) << (j*8);
	if ((bits % 32) != 0)
		v.data.back() &= 0xffffffff >> (32 - (bits % 32));
	return v;
}

bool BigInt::miller_rabin_prime(const BigInt &p, int count) {
	// decompose
	int s = 0;
	BigInt d = p-1;
	// TODO improve me!!!
	while ((d.data[0] & 1) == 0) {
		unsigned int rem;
		d.div(2, rem);
		s ++;
	}
	int bits = p.count_bits();

	// trials...
	BigInt p_mm = p - 1;
	for (int i=0; i<count; i++) {
		BigInt a;
		do {
			a = BigInt::rand(bits);
		} while ((a > p) || (a <= 1));

		BigInt rem;
		BigInt t = BigInt::pow_mod(a, d, p);
		if (t == 1)
			continue;
		if (t == p_mm)
			continue;

		bool passed = true;
		for (int r=1;r<s;r++) {
			t *= t;
			t.div(p, rem);
			t = rem;
			if (t == p_mm) {
				passed = false;
				break;
			}
		}
		if (!passed)
			continue;
		return false;

	}
	return true;
}

void BigInt::get_prime(BigInt &p, int bits) {
	do {
		p = BigInt::rand(bits-1);
		p = p * 2;
		p += 1;
	} while (!miller_rabin_prime(p, 30));
}

bool BigInt::find_coprime(BigInt &e, BigInt &phi) {
	int bits = phi.count_bits();
	do {
		e = BigInt::rand(bits);
	} while (e >= phi);

	while(e > 1) {
		if (BigInt::gcd(e, phi) == 1)
			return true;
		e -= 1;
	}
	return false;
}

bool BigInt::find_mod_inverse(BigInt &d, BigInt &e, BigInt &phi) {
	/*d = 1;
	while(d < e){
		vli n = d * e;
		vli rem;
		n._div(phi, rem);
		if (rem == 1)
			return true;
		d += 1;
	}
	return false;*/

	// via extended Euclidean algorithm
	BigInt a = e;
	BigInt b = phi;
	BigInt x = 0;
	BigInt y = 1;
	BigInt last_x = 1;
	BigInt last_y = 0;
	BigInt vli0 = 0;
	BigInt rem;
	while (b != vli0) {
		BigInt q;
		a.div(b, rem);
		q = a;

		a = b;
		b = rem;
		BigInt temp = last_x;
		last_x = x;
		x = temp - q*x;
		temp = last_y;
		last_y = y;
		BigInt yy = temp - q*y;
		y = yy;
	}
	d = last_x;
	while (d.sign)
		d += phi;
	while (d > phi)
		d -= phi;

	BigInt ttt = d * e;
	ttt._div(phi, rem);
	if (rem != 1) {
		printf("--- 1=%s  (d=%s)\n", rem.to_string().c_str(), d.to_string().c_str());
		return false;
	}
	return true;
}
