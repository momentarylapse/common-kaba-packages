/*
 * crypto.cpp
 *
 *  Created on: 16.01.2013
 *      Author: michi
 */

#include "../base/base.h"
#include "vli.h"
#include "crypto.h"
#include <stdio.h>

void CryptoRSACreateKey_trial(Crypto &key1, Crypto &key2, int bits)
{
	BigInt p, q;
	BigInt::get_prime(p, bits/2);
	BigInt::get_prime(q, bits/2);
	BigInt n = p * q;
	BigInt phi = (p - 1) * (q - 1);
	BigInt d, e;
	if (!BigInt::find_coprime(e, phi))
		throw "Crypto: no coprime found";
	if (!BigInt::find_mod_inverse(d, e, phi))
		throw "Crypto: no inverse";
	key1.n = n;
	key1.k = e;
	key2.n = n;
	key2.k = d;
}

void CryptoCreateKeys(Crypto &key1, Crypto &key2, const string &type, int bits)
{
	if (type != "rsa")
		return;
	for (int i=0; i<100; i++){
		try{
			CryptoRSACreateKey_trial(key1, key2, bits);
			return;
		}catch(...){
		}
	}
	throw "Crypto: no key found...";
}

BigInt str2vli(const string &str, int offset, int bytes) {
	string t = str.sub(offset, offset + bytes);
	t.resize(bytes);
	BigInt v;
	v.data.resize((bytes - 1) / 4 + 1);
	memcpy(v.data.data, t.data, bytes);
	return v;
}

string vli2str(BigInt &v, int bytes) {
	string t;
	t.resize(bytes);
	memcpy(t.data, v.data.data, v.data.num * 4);
	return t;
}

bytes Crypto::encrypt(const bytes &s) const {
	string r;
	int bytes = this->n.count_bits() / 8;
	int offset = 0;
	do {
		BigInt m = str2vli(s, offset, bytes);
		m = BigInt::pow_mod(m, this->k, this->n);
		r += vli2str(m, bytes + 1);
		offset += bytes;
	}while (offset < s.num);
	return r;
}

bytes Crypto::decrypt(const bytes &s, bool cut) const {
	string r;
	int bytes = this->n.count_bits() / 8;
	int offset = 0;
	do {
		BigInt m = str2vli(s, offset, bytes+1);
		m = BigInt::pow_mod(m, this->k, this->n);
		r += vli2str(m, bytes);
		offset += bytes + 1;
	} while (offset < s.num);

	if (cut)
		for (int i=0;i<r.num;i++)
			if (r[i] == 0){
				r.resize(i);
				break;
			}
	return r;
}

void Crypto::from_str(const string &s) {
	Array<string> ss = s.explode(":");
	if (ss.num != 2)
		return;
	string h1 = ss[0].unhex();
	n = str2vli(h1, 0, h1.num);
	string h2 = ss[1].unhex();
	k = str2vli(h2, 0, h2.num);
}

string Crypto::str() {
	int bytes_n = (n.count_bits() + 7) / 8;
	int bytes_k = (n.count_bits() + 7) / 8;
	return vli2str(n, bytes_n).hex() + ":" + vli2str(k, bytes_k).hex();
	//return n.dump() + " " + k.dump();
}

