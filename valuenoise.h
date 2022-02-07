#ifndef _PERLIN
#define _PERLIN 1

#include "math_tools.h"
#include <map>

int luRand(int lower, int upper);
int xyRand(long long xc, long long yc);
float xyNoise(long long xc, long long yc);

class ValueNoiseGrid
{
    private:
    float scale;
    long long seed;

    int xyRand(long long xc, long long yc);
    float xyNoise(long long xc, long long yc);
    std::map< std::pair<int, int>, float > precomputed;

    public:
    ValueNoiseGrid(float _scale, long long _seed);
    ~ValueNoiseGrid();

    float getVal(float x, float y);

    float getScale();
};

#endif