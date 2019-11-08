#ifndef _PERLIN
#define _PERLIN 1

int luRand(int lower, int upper);
int xyRand(long long xc, long long yc);

class PerlinGrid
{
    public:
    Vec2f* VECTOR_LOOKUP[4] = {new Vec2f(1, 0), new Vec2f(0, 1), new Vec2f(-1, 0), new Vec2f(0, -1)};

    PerlinGrid(int scale);
    ~PerlinGrid();

    float getVal(float x, float y);

    Vec2f* getNodeVector(int x, int y);
};

#endif