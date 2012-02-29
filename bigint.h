#pragma once
#include <gmp.h>

struct BigInt {

	mpz_t n;

public:
	BigInt();
	void copy(BigInt& other);
	bool read();
};
