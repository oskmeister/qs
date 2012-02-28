#include "sieve.h"

/*
TODO only use primes which are quadratic residues!
TODO use bitset
*/

/* smoothness bound B */
#define B 294
/* upper bound of pi(B) (+1) */
#define max_pB 63
/* number of smooth numbers */
#define smooth_find 64

int pB = 0; /* pi(B) */

int notPrime[B];

/* list of inital primes */
int prime_list[max_pB]; 

/* prime sieve */
void primes(int n){
  for(int i = 2; i<B; i++){
    if(!notPrime[i]){
      for(int j = 2; j*i<B; j++){
        notPrime[i*j] = 1;
      }
    }
  }
  for(int i = 2; i<B; i++){
    if(!notPrime[i]){
      prime_list[pB] = i;
      pB++;
    }
  }
  dprintf("setting pi(%d) = %d\n", B, pB);
}

/* how many numbers should be generated at a time? */
#define a_count 100


mpz_t orig[a_count];
mpz_t sieved[a_count];
mpz_t table[smooth_find];
int smooth_found = 0;
unsigned long long bitset[max_pB];

/* initalize sieve */
void initAll(){
  dprintf("init!\n");
  primes(B);
  dprintf("initial primes found\n");
  for(int i = 0; i<a_count; i++){
    mpz_init(orig[i]);
    mpz_init(sieved[i]);
  }
  for(int i = 0; i<max_pB; i++){
    mpz_init(table[i]);
  }
  dprintf("init done!\n");
}

int find_factors(mpz_t number){
  dprintf("data gathered - time to solve!\n");

}

void sieve(mpz_t number){
  /* if probable prime, just print */
  if(mpz_probab_prime_p(number, 10)){
    dprintf("is probable prime!\n"); 
    gmp_printf("%Zd\n", number);
    return;
  }
  if(!pB){
    initAll();
  }
  /* find smooth numbers to check for squares with */
  mpz_t a;
  mpz_init(a); 
  mpz_root(a, number, 2);
  mpz_add_ui(a, a, 1);
  dgmp_printf("initial a = %Zd\n", a);
  while(1){
    dgmp_printf("next pass: a = %Zd\n", a);
    smooth_found = 0;
    while(smooth_found < smooth_find){
      /* generate sieving field */
      for(int i = 0; i<a_count; i++){
        mpz_mul(orig[i], a, a);  
        mpz_sub(orig[i], orig[i], number);
        mpz_set(sieved[i], orig[i]);
        dgmp_printf("a^2 - n val: %Zd\n", orig[i]);
        mpz_add_ui(a, a, 1);
      }
      /* check if smooth */
      for(int i = 0; i<pB; i++){
        int prime = prime_list[i];
        dprintf("check prime %d\n", prime);
        for(int j = 0; j<prime && j < a_count; j++){
          if(mpz_divisible_ui_p(sieved[j], prime)){
            for(int k = j; k<a_count; k+=prime){
              do {
                mpz_div_ui(sieved[k], sieved[k], prime);
              } while(mpz_divisible_ui_p(sieved[k], prime));
            }
          }
        }
      }
      for(int i = 0; i<a_count && smooth_found < smooth_find; i++){
        if(!mpz_cmp_ui(sieved[i], 1)){
          dgmp_printf("number %Zd is smooth!\n", orig[i]);
          mpz_set(table[smooth_found++], orig[i]);
        }
      }
    }
    dprintf("found all smooth numbers!\n");
    dprintf("they are:\n");
    for(int i = 0; i<smooth_found; i++){
      dgmp_printf("%Zd ( ", table[i]);
      mpz_t tmp;
      mpz_init(tmp);
      mpz_set(tmp, table[i]);
      bitset[i] = 0;
      for(int j = 0; j<pB; j++){
        int prime = prime_list[j];
        int d = 0;
        while(mpz_divisible_ui_p(tmp, prime)){
          mpz_div_ui(tmp, tmp, prime);
          d ^= 1;
        }
        if(d) bitset[i] |= (1<<j);
        dprintf("%d", d);
      }
      dprintf("), ");
    }
    dprintf("\n");
    if(find_factors(number)){
      break;
    }
  }
}

