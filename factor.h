#pragma once
#include "sieve.h"
#include <vector>
#include "settings.h"
#include <gmp.h>
#include <gmpxx.h>

struct factor {

	mpz_class N;

	std::vector<int> primes;
	std::vector<int> prime_base;

	mpz_class sieveField[FIELD_SIZE];
	mpz_class origField[FIELD_SIZE];
	mpz_class xField[FIELD_SIZE];
	mpz_class sq, y;
	int found, x;
	std::vector<std::pair<mpz_class, mpz_class> > smooth;

public:
	factor(mpz_class _N, std::vector<int> _primes){
		N = _N;
		primes = _primes;
		generatePrimeBase();
		sq = sqrt(N);
		dgmp_printf("Sqrt: %Zd\n", sq.get_mpz_t());
		sq += 1;
		x = 0;
	}
	std::pair<mpz_class, mpz_class> go();

private:
	void generatePrimeBase();
	bool lagrange(int n);
	void generateField();
	void doSieve();
	std::bitset<BASE_BOUND+2> solveMatrix();
};
