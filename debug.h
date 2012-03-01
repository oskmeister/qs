#pragma once
//Some debug macros. Compile with -DDEBUG for debug output
//#define DEBUG
#ifdef DEBUG

#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#define dgmp_printf(...) gmp_fprintf(stderr, __VA_ARGS__)

#else

#define dprintf if(false) printf
#define dgmp_printf if(false) gmp_printf

#endif

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define egmp_printf(...) gmp_fprintf(stderr, __VA_ARGS__)
