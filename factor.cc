#include "factor.h"
#include <cstdlib>


std::pair<mpz_class, mpz_class> factor::go(){
	int misses = 0;
	while(true){
		while((int)smooth.size() <= (int)prime_base.size()){
			dprintf("Found: %lu\n", smooth.size());
			generateField();
			dprintf("Generated field\n");
			doSieve();
		}
		dprintf("Now has %lu smooth - base %lu\n", smooth.size(), prime_base.size());
		std::bitset<BASE_BOUND+2> solved = solveMatrix();
		dprintf("Matrix has been solved\n");
		for(int i = 0; i<(int)smooth.size(); i++){
			dgmp_printf("%Zd ", smooth[i].first.get_mpz_t());
		}
		mpz_class x = 1;
		mpz_class y = 1;
		dprintf("[");
		for(int i = 0; i<(int)smooth.size(); i++){
			dgmp_printf("Smooth %d : %Zd %Zd\n", i, smooth[i].first.get_mpz_t(), smooth[i].second.get_mpz_t());
			if(!solved[i]) continue;
			dprintf("%d ", i);
			x *= smooth[i].first;
			y *= smooth[i].second;
		}
		dprintf("]\n");
		x = sqrt(x);
		dgmp_printf("End product: %Zd and %Zd\n", x.get_mpz_t(), y.get_mpz_t());

		mpz_class res;
		mpz_class sum = x+y;
		mpz_gcd(res.get_mpz_t(), sum.get_mpz_t(), N.get_mpz_t());
		if(res == 1 || res == N){
			sum = x-y;
			mpz_gcd(res.get_mpz_t(), sum.get_mpz_t(), N.get_mpz_t());
		}

		dgmp_printf("Result: %Zd\n", res.get_mpz_t());
		fflush(stdout);
		if(res == 1 || res == N){
			smooth.clear();
			misses++;
			if(misses >= 4){
				N = 1;
				return std::make_pair(N, N);
			}
		} else {
			mpz_class a = N/res;
			mpz_class b = res;
			return std::make_pair(a, b);
		}
	}
}

std::bitset<BASE_BOUND+2> factor::solveMatrix(){
	matrix<BASE_BOUND, BASE_BOUND+2> m;
	mpz_class tmp;
	for(int j = 0; j<(int)smooth.size(); j++){
		dgmp_printf("checking smooth number: %Zd\n", smooth[j].first.get_mpz_t());
		tmp = smooth[j].first;
		for(int i = 0; i<(int)prime_base.size(); i++){
			while(tmp%prime_base[i] == 0){
				m[i][j] = m[i][j]^true;
				tmp /= prime_base[i];
			}
		}
	}
	std::bitset<BASE_BOUND+2> solution = m.solve();
	for(int i = 0; i<= BASE_BOUND; i++){
		if(solution[i]){
			std::pair<mpz_class, mpz_class> ints = smooth[i];
			dgmp_printf("Included: %Zd and %Zd\n", ints.first.get_mpz_t(), ints.second.get_mpz_t());
		}
	}
	return solution;
}

//TODO actually sieve instead of brute force..
void factor::doSieve(){
	//printf("Prime base: %lu, field size: %d\n", prime_base.size(), FIELD_SIZE);
	for(int i = 0; i<(int)prime_base.size(); i++){
		for(int j = 0; j<FIELD_SIZE; j++){
			if(sieveField[j]%prime_base[i] == 0){
				for(int k = j; k<FIELD_SIZE; k += prime_base[i]){
					do {
						sieveField[k] /= prime_base[i];
					} while(sieveField[k]%prime_base[i] == 0);
				}
			}
		}
	}
	for(int i = 0; i<FIELD_SIZE && smooth.size() <= prime_base.size(); i++){
		if(sieveField[i] == 1){
			mpz_class n(origField[i]);
			mpz_class m(xField[i]);
			smooth.push_back(std::make_pair(n, m));
			dgmp_printf("Found smooth: %Zd\n", origField[i].get_mpz_t());
		}
	}
	if(smooth.size() == prime_base.size()+1){
		dprintf("Found enough!\n");	
	}
}

void factor::generateField(){
	//int a = rand()%100;
	int a = 1;
	dgmp_printf("Field: (x = %d) ", x);
	for(int i = 0; i<FIELD_SIZE; i++){
		mpz_class xx = (a*(x++)) + sq;
		mpz_class y = xx*xx - N;
		sieveField[i] = y;
		origField[i] = y;
		xField[i] = xx;
		//dgmp_printf("%Zd ", origField[i]);
	}
}

void factor::generatePrimeBase(){
	dprintf("Generating prime base...\n");
	for(int i = 0; i<(int)primes.size() && (int)prime_base.size() < BASE_BOUND; i++){		
		dprintf("Testing %d\n", primes[i]);
		if(lagrange(primes[i])){
			prime_base.push_back(primes[i]);
			dprintf("%d seems like a good prime\n", primes[i]);
		}
	}
	if((int)prime_base.size() < BASE_BOUND){
		dprintf("Not enough primes!\n");
		abort();
	}
	dprintf("Generated base!\n");
}

/*
	Calculates the lagrange symbol (a/n) where n is prime
*/
bool factor::lagrange(int p){
	if(p == 2) return true;
	mpz_class n = p;

	mpz_class a = N;

	mpz_class q = (p-1)/2;

	mpz_class x = q;

	mpz_class z = 1;
	
	a %= n;
	while(x != 0){
		if(x%2 == 0){
			a = (a*a)%n;
			x /= 2;
		} else {
			x = x-1;
			z = (z*a)%n;
		}
	}
	dgmp_printf("lagrange = %Zd\n", z.get_mpz_t());
	if(z == 1) return true;
	return false;
}
