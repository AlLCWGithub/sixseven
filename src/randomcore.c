#include "randomcore.h"
#include <stdint.h>
#include <stddef.h>
#include <time.h>

/*
Uses splitmix64 to spread out the seed

Uses MT19937-64 as the core generator:
* The period is 2**19937-1.
* If I read CPython's source code for random.py correctly, it says the generator is super safe.
*/

#define MTM 312
#define MTN 156
#define MTMATRIXA 0xB5026F5AA96619E9ULL
#define MTUPPERMASK 0xFFFFFFFF80000000ULL
#define MTLOWERMASK 0x7FFFFFFFULL

static uint64_t _mt[MTM];
static int _mti = MTM;

static uint64_t _splitmix(uint64_t *seed){
uint64_t z = (*seed += 0x9E3779B97F4A7C15ULL);
z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
return z ^ (z >> 31);
}

void rcseed(uint64_t seed){
for(int i = 0; i < MTM; ++i){
_mt[i] = _splitmix(&seed);
}
_mti = MTM;
}

uint64_t rcuint64(){
uint64_t y;
static uint64_t mag01[2] = {0x0ULL, MTMATRIXA};
if(_mti >= MTM){
int kk;
for(kk = 0; kk < MTM - MTN; ++kk){
y = (_mt[kk] & MTUPPERMASK) | (_mt[kk + 1] & MTLOWERMASK);
_mt[kk] = _mt[kk + MTN] ^ (y >> 1) ^ mag01[y & 0x1ULL];
}
for(; kk < MTM -1; ++kk){
y = (_mt[kk] & MTUPPERMASK) | (_mt[kk + 1] & MTLOWERMASK);
_mt[kk] = _mt[kk + (MTN - MTM)] ^ (y >> 1) ^ mag01[y & 0x1ULL];
}
y = (_mt[MTM - 1] & MTUPPERMASK) | (_mt[0] & MTLOWERMASK);
_mt[MTM - 1] = _mt[MTN - 1] ^ (y >> 1) ^ mag01[y & 0x1ULL];
_mti = 0;
}
y = _mt[_mti++];
y ^= (y >> 29) & 0x5555555555555555ULL;
y ^= (y << 17) & 0x71D67FFFEDA60000ULL;
y ^= (y << 37) & 0xFFF7EEE000000000ULL;
y ^= (y >> 43);
return y;
}
