#ifndef _VLI_INCLUDED_
#define _VLI_INCLUDED_

struct BigInt {
	BigInt();
	BigInt(const BigInt &v);
	BigInt(int v);
	BigInt(const string &str);
	~BigInt();

private:
	void shift_bits(int n);
	void shift_units(int n);
	void add_abs(const Array<unsigned int> &_data);
	void sub_abs(const Array<unsigned int> &_data);
	void mul_ui(unsigned int i);
	void normalize();

public:
	void _cdecl operator = (const BigInt &v);
	void _cdecl operator += (const BigInt &v);
	void _cdecl operator -= (const BigInt &v);
	void _cdecl operator *= (const BigInt &v)
	{	*this = *this * v;	}
	BigInt _cdecl operator + (const BigInt &v) const
	{	BigInt r = *this; r += v;	return r;	}
	BigInt _cdecl operator - (const BigInt &v) const
	{	BigInt r = *this; r -= v;	return r;	}
	BigInt _cdecl operator * (const BigInt &v) const;
	void _cdecl div(unsigned int divisor, unsigned int &remainder);
	void _cdecl div(const BigInt &divisor, BigInt &remainder);
	int _cdecl compare_abs(const BigInt &v) const;
	int _cdecl compare(const BigInt &v) const;
	bool _cdecl operator == (const BigInt &v) const;
	bool _cdecl operator != (const BigInt &v) const
	{	return !(*this == v);	}
	bool _cdecl operator < (const BigInt &v) const;
	bool _cdecl operator <= (const BigInt &v) const
	{	return !(v < *this);	}
	bool _cdecl operator > (const BigInt &v) const
	{	return (v < *this);	}
	bool _cdecl operator >= (const BigInt &v) const
	{	return !(*this < v);	}
	string _cdecl to_string() const;
	string _cdecl dump() const;

	int count_bits() const;

	// higher functions
	static BigInt pow(const BigInt &x, const BigInt &e);
	static BigInt pow_mod(const BigInt &x, const BigInt &e, const BigInt &m);
	static BigInt gcd(const BigInt &a, const BigInt &b);
	static BigInt rand(int bits);
	static bool miller_rabin_prime(const BigInt &p, int count);
	static void get_prime(BigInt &p, int bits);
	static bool find_coprime(BigInt &e, BigInt &phi);
	static bool find_mod_inverse(BigInt &d, BigInt &e, BigInt &phi);

	// kaba
	void _cdecl idiv(const BigInt &d, BigInt &rem)
	{	div(d, rem);	}
	BigInt _cdecl _div(const BigInt &d, BigInt &rem) const
	{	BigInt r = *this;	r.div(d, rem);	return r;	}

	// data
	bool sign;
	Array<unsigned int> data;
};

#endif
