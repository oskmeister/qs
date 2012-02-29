#include "bigint.h"


BigInt::BigInt(){
	mpz_init(n);
}

void BigInt::copy(BigInt& other){
	mpz_set(n, other.n);
}

bool BigInt::read(){
	return gmp_scanf("%Zd", n) == 1;
}
