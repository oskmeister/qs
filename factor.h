#pragma once
#include "sieve.h"
#include "bigint.h"
#include <vector>

struct factor {

	BigInt N;
	std::vector<int> primes;

public:
	factor(BigInt& _N, std::vector<int>& _primes){
		N.copy(_N);
		primes = _primes;
	}
	std::pair<BigInt, BigInt> go();
};
