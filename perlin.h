#ifndef _PERLIN
#define _PERLIN 1

#include "math_tools.h"

int luRand(int lower, int upper);
int xyRand(long long xc, long long yc);
float xyNoise(long long xc, long long yc);

class PerlinGrid
{
    int scale;
    public:
    Vec2f* VECTOR_LOOKUP[8] = {new Vec2f(1, 0), new Vec2f(0, 1), new Vec2f(-1, 0), new Vec2f(0, -1), new Vec2f( 0.70710678118,  0.70710678118), new Vec2f( -0.70710678118,  0.70710678118), new Vec2f( 0.70710678118,  -0.70710678118), new Vec2f( -0.70710678118,  -0.70710678118)};

    PerlinGrid(int _scale);
    ~PerlinGrid();

    float getVal(float x, float y);

    Vec2f* getNodeVector(int x, int y);
};

#endif