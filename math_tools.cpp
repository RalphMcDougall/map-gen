#include "math_tools.h"

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