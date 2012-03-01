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
	bool ok = gmp_scanf("%Zd", N.get_mpz_t());
	if(!ok){
		dprintf("Invalid input!\n");
		return false;
	} else {
		dgmp_printf("Got input: %Zd\n", N.get_mpz_t());
		return true;
	}
}

/*
	Begin factoring!
*/
void sieve::go(){
	dprintf("Begin factoring!\n");
	std::queue<mpz_class> toFactor;
	toFactor.push(N);
	/*
		Continously factor the number.
		If probably prime, output as factor
		Else - split into 2 factors, and keep factoring them
	*/
	while(!toFactor.empty()){
		mpz_class next = toFactor.front(); toFactor.pop();
		dgmp_printf("Next number to factor: %Zd\n", next.get_mpz_t());
		if(mpz_probab_prime_p(next.get_mpz_t(), 10)){
			gmp_printf("%Zd\n", next.get_mpz_t());
			continue;
		}
		if(false && next < 1e9){
			signed long int num = mpz_get_si(next.get_mpz_t());
			for(int i = 2; i*i <= num; i++){
				while(num%i == 0){
					printf("%d\n", i);
					num /= i;
				}
			}
			if(num != 1) printf("%ld\n", num);
			continue;
		}
		factor* f = new factor(next, primes);
		std::pair<mpz_class, mpz_class> factors = f->go();
		if(!mpz_cmp_ui(factors.first.get_mpz_t(), 1)){
			printf("fail\n");
			break;
		}
		toFactor.push(factors.first);
		toFactor.push(factors.second);
		delete f;
	}
}


