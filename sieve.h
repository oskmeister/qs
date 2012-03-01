#pragma once
#include <gmp.h>
#include <gmpxx.h>	
#include <vector>
#include "debug.h"
#include "matrix.h"
#include "factor.h"
#include <queue>


/*
	Main prime sieve
*/
struct sieve {

	mpz_class N;

	std::vector<int> primes;

public:
	sieve();
	void go();
	bool input();
	void setPrimes(std::vector<int>& _primes){
		dprintf("set primes!\n");
		primes = _primes;
		dprintf("done set primes!\n");
	}
};

