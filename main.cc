/**
 *  main.cc
 *	Quadratic Sieve implementation
 *
 *	(c) Johan Sannemo Oskar Werkelin Ahlin
 **/

#include <cstdio>
#include <vector>
#include <gmp.h>
#include "debug.h"
#include "sieve.h"
#include "primes.h"
#include "settings.h"
#include "matrix.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(NULL));
	//Generate initial prime sieve
	prime_sieve* primes = new prime_sieve(PRIMES_BOUND);
	std::vector<int> prime_list = primes->sieve();
	dprintf("Generated %lu primes\n", prime_list.size());
	delete primes;
	//Read numbers from stdin
	//Quit on invalid input (non-numeric, EOF etc)
	//Will print the factors in random order to stdout
	while(true){
		sieve siever;
		if(!siever.input()) break;
		siever.setPrimes(prime_list);
		siever.go();
		printf("\n");
	}
  return 0;
}
