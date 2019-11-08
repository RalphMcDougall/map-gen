#include "world.h"
#include <stdlib.h>
#include "math_tools.h"

World::World(int _width, int _height, int _numLayers, long long _seed)
{
    width = _width;
    height = _height;
    numLayers = _numLayers;
    seed = _seed;

    valMap = (float*) malloc(width * height * sizeof(float));
    gridLayers = (PerlinGrid**) malloc(numLayers * sizeof(PerlinGrid*) );

    int scale = START_SCALE;

    for (int i = 0; i < numLayers; ++i)
    {
        gridLayers[i] = new PerlinGrid(scale, seed + i);
        scale /= 2;
    }
    buildWorld();

}
World::~World()
{
    free(valMap);
    for (int i = 0; i < numLayers; ++i)
    {
        free(gridLayers[i]);
    }
    free(gridLayers);
}

void World::setVal(float v, int x, int y)
{
    valMap[y * width + x] = v;
}
float World::getVal(int x, int y)
{
    return valMap[y * width + x];
}

void World::buildWorld()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float h = 0;
            for (int i = 0; i < numLayers; ++i)
            {
                h += gridLayers[i]->getVal(x, y) * (gridLayers[i]->getScale() / START_SCALE);
            }
            setVal(h, x, y);
        }
    }
}

unsigned int World::getColour(int x, int y)
{
    float v = getVal(x, y);
    if (v < 0)
    {
        return 0x0000FF; // BLUE
    }
    else if (v >= 0)
    {
        return 0x00FF00; // GREEN
    }
}