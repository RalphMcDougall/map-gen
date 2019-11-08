#include "math_tools.h"
#include <math.h>

Vec2f::Vec2f(float _x, float _y)
{
    x = _x;
    y = _y;
}

float dot(const Vec2f* v1, const Vec2f* v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

float lerp(float v, float l, float u)
{
    return l + v * (u - l);
}

float smooth(float v, float l, float u)
{
    if (l == u)
    {
        if (v < l) return 0;
        return 1;
    }

    float c = clamp((v - l) / (u - l), 0, 1);
    return c * c * (3 - 2 * c);//c * c * c * (c * (c * 6 - 15) + 10);
}

float clamp(float v, float l, float u)
{
    if (v > u) return u;
    if (v < l) return l;
    return v;
}

float cosInterpolate(float v, float l, float u)
{
    float ft = v * 3.1415926535;
    float f = (1.0 - cos(ft)) * 0.5;
    return lerp(f, l, u);
}