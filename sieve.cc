#include "sieve.h"



/*
	Initialize new prime sieve
*/
sieve::sieve(){
	dprintf("Initalize new sieve...\n");
}

/*
	Read prime from stdin
*/
bool sieve::input(){
	bool ok = N.read();
	if(!ok){
		dprintf("Invalid input!\n");
		return false;
	} else {
		dgmp_printf("Got input: %Zd\n", N.n);
		return true;
	}
}

/*
	Begin factoring!
*/
void sieve::go(){
	dprintf("Begin factoring!\n");
	std::queue<BigInt> toFactor;
	toFactor.push(N);
	/*
		Continously factor the number.
		If probably prime, output as factor
		Else - split into 2 factors, and keep factoring them
	*/
	while(!toFactor.empty()){
		BigInt next = toFactor.front(); toFactor.pop();
		dgmp_printf("Next number to factor: %Zd\n", next.n);
		if(mpz_probab_prime_p(next.n, 25)){
			dprintf("Factor: ");
			gmp_printf("%Zd\n", next.n);
			continue;
		}
		factor* f = new factor(next, primes);
		std::pair<BigInt, BigInt> factors = f->go();
		toFactor.push(factors.first);
		toFactor.push(factors.second);
		delete f;
	}
}


