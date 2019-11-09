#ifndef _WORLD
#define _WORLD 1

#include "perlin.h"

class Biome
{
    public:
    unsigned int colour;
    float startH;

    Biome(unsigned int colour, float startH);
};

class World
{
    private:
    const int START_SCALE = 256;
    int width, height, numLayers;
    long long seed;
    float * valMap;
    PerlinGrid** gridLayers;
    float maxV, minV;

    int colourMode = 1;

    int numBiomes;
    Biome** biomes;

    void buildWorld();
    void establishBounds();

    public:
    World(int width, int height, int numLayers, long long seed);
    ~World();

    void setVal(float v, int x, int y);
    float getVal(int x, int y);
    unsigned int getColour(int x, int y);
    void setColourMode(int m);
};


#endif