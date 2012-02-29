#pragma once
//Some debug macros. Compile with -DDEBUG for debug output
#define DEBUG
#ifdef DEBUG

#define dprintf printf
#define dgmp_printf gmp_printf

#else

#define dprintf if(false) printf
#define dgmp_printf if(false) gmp_printf

#endif
