#include "perlin.h"
#include <stdlib.h>

long long SEED = 1; // Random number generator seed

int xyRand(long long xc, long long yc)
{
    // Return a random integer for a given x and y coordinate. This should be a pure function.
    const long long FACTOR = 10248304983459; // Magic constant
    srand(SEED + FACTOR * xc + yc);

    return rand();
}