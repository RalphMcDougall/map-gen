#include "math_tools.h"
#include "perlin.h"
#include <stdlib.h>

long long SEED = 1; // Random number generator seed

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

PerlinGrid::PerlinGrid(int scale)
{
    // Initialise the possible vectors that can be at each grid node
    VECTOR_LOOKUP[0] = new Vec2f(1, 0);
    VECTOR_LOOKUP[1] = new Vec2f(-1, 0);
    VECTOR_LOOKUP[2] = new Vec2f(0, 1);
    VECTOR_LOOKUP[3] = new Vec2f(0, -1);
}

PerlinGrid::~PerlinGrid()
{
    // Free assets associated with the grid
    for (int i = 0; i < 4; ++i)
    {
        free(VECTOR_LOOKUP[i]);
    }
}

Vec2f* PerlinGrid::getNodeVector(int x, int y)
{
    return VECTOR_LOOKUP[ xyRand(x, y) % 4 ];
}

float PerlinGrid::getVal(float x, float y)
{
    int x0 = (int) x;
    int x1 = x0 + 1;
    int y0 = (int) y;
    int y1 = y0 + 1;

    Vec2f v1(x - x0, y - y0);
    Vec2f v2(x - x1, y - y0);
    Vec2f v3(x - x0, y - y1);
    Vec2f v4(x - x1, y - y1);

    float d1 = dot(&v1, getNodeVector(x0, y0));
    float d2 = dot(&v2, getNodeVector(x1, y0));
    float d3 = dot(&v3, getNodeVector(x0, y1));
    float d4 = dot(&v4, getNodeVector(x1, y1));

    float l1 = lerp(x - x0, d1, d2);
    float l2 = lerp(x - x0, d3, d4);

    float v = lerp(y - y0, l1, l2);
    return v;
}