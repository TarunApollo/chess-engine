#include "magic_random.h"

static U64 rng_state = 0x123456789abcdef0ULL;
static const U64 constant1 = 0xbf58476d1ce4e5b9;
static const U64 constant2 = 0x94d049bb133111eb ;


static inline U64 spm64(){
    rng_state +=  0x9e3779b97f4a7c15;
    U64 z = rng_state;
    z = (z ^ (z >> 30)) * constant1;
    z = (z ^ (z >> 27)) * constant2;
    z = (z ^ (z >> 31));
    return z;
}

U64 magic_random_candidate(void){
    return spm64() & spm64() & spm64();
}

