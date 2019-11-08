#include "math_tools.h"
#include "perlin.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

long long SEED = time(0);//1; // Random number generator seed

int luRand(int lower, int upper)
{
    // return a random number in the range [lower, upper)
    int r = rand();
    return lower + r % (upper - lower);
}

int xyRand(long long xc, long long yc)
{
    // Return a random integer for a given x and y coordinate. This should be a pure function.
    const long long FACTOR = 2038074743; // Magic prime constant
    srand(SEED + FACTOR * xc + yc);

    return rand();
}

float xyNoise(long long xc, long long yc)
{
    // Get the noise value in the range [-1, 1] for (x, y)

    float r = 1.0 * xyRand(xc, yc) / INT32_MAX;
    return 2 * r - 1;
}

PerlinGrid::PerlinGrid(int _scale)
{
    // Initialise the possible vectors that can be at each grid node
    /*VECTOR_LOOKUP[0] = new Vec2f( 0.70710678118,  0.70710678118);
    VECTOR_LOOKUP[1] = new Vec2f(-0.70710678118,  0.70710678118);
    VECTOR_LOOKUP[2] = new Vec2f( 0.70710678118, -0.70710678118);
    VECTOR_LOOKUP[3] = new Vec2f(-0.70710678118, -0.70710678118);*/
    scale = _scale;
}

PerlinGrid::~PerlinGrid()
{
    // Free assets associated with the grid
    for (int i = 0; i < (sizeof(VECTOR_LOOKUP) / sizeof(Vec2f*)); ++i)
    {
        free(VECTOR_LOOKUP[i]);
    }
}

Vec2f* PerlinGrid::getNodeVector(int x, int y)
{
    return VECTOR_LOOKUP[ xyRand(x, y) % (sizeof(VECTOR_LOOKUP) / sizeof(Vec2f*)) ];
}

float PerlinGrid::getVal(float x, float y)
{
    x /= scale;
    y /= scale;

    int x0 = (int) x;
    int x1 = x0 + 1;
    int y0 = (int) y;
    int y1 = y0 + 1;

    float sx = x - x0;
    float sy = y - y0;

    float v1 = xyNoise(x0, y0);
    float v2 = xyNoise(x1, y0);
    float v3 = xyNoise(x0, y1);
    float v4 = xyNoise(x1, y1);

    float d1 = cosInterpolate(sx, v1, v2);
    float d2 = cosInterpolate(sx, v3, v4);

    float v = cosInterpolate(sy, d1, d2);

    return v;
}