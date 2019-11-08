#ifndef _MATH_TOOLS
#define _MATH_TOOLS 1

class Vec2f
{
    public:
    float x, y;
    Vec2f(float x, float y);
};

float dot(const Vec2f* v1, const Vec2f* v2);
float lerp(float v, float l, float u);

#endif