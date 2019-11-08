#ifndef _WORLD
#define _WORLD 1

#include "perlin.h"

class World
{
    private:
    const int START_SCALE = 256;
    int width, height, numLayers;
    long long seed;
    float * valMap;
    PerlinGrid** gridLayers;

    void buildWorld();

    public:
    World(int width, int height, int numLayers, long long seed);
    ~World();

    void setVal(float v, int x, int y);
    float getVal(int x, int y);
    unsigned int getColour(int x, int y);
};


#endif