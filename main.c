/**
 *  main.cpp
 *	Quadratic Sieve implementation
 *
 *	(c) Johan Sannemo Oskar Werkelin Ahlin
 **/
#include "main.h"

int main() {
  dprintf("Begin main\n");
  mpz_t N;
  mpz_init(N);
  for(int i = 0; i<100; i++){
    gmp_scanf("%Zd", N);
    dgmp_printf("factoring: %Zd\n", N);
    sieve(N);
  }
  return 0;
}
