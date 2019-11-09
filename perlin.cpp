#include "math_tools.h"
#include "perlin.h"
#include <iostream>
#include <map>

int luRand(int lower, int upper)
{
    // return a random number in the range [lower, upper)
    int r = rand();
    return lower + r % (upper - lower);
}

int PerlinGrid::xyRand(long long xc, long long yc)
{
    // Return a random integer for a given x and y coordinate. This should be a pure function.
    const long long FACTOR = 2038074743; // Magic prime constant
    srand(seed + FACTOR * xc + yc);

    return rand();
}

float PerlinGrid::xyNoise(long long xc, long long yc)
{
    // Get the noise value in the range [-1, 1] for (x, y)
    std::pair<long long, long long> p = {xc, yc};
    if (precomputed.count(p) == 0)
    {
        float r = 1.0 * xyRand(xc, yc) / INT32_MAX;
        precomputed[p] = 2 * r - 1;
    }
    return precomputed[p];
}

PerlinGrid::PerlinGrid(float _scale, long long _seed)
{
    scale = _scale;
    seed = _seed;
}

PerlinGrid::~PerlinGrid()
{
    
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

float PerlinGrid::getScale()
{
    return scale;
}