#pragma once
#include <gmp.h>

/*
	Wrapper around mpz_t
*/

struct BigInt {

	mpz_t n;

public:
	BigInt();
	void copy(BigInt& other);
	bool read();
};
