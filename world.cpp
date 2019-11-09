#include "world.h"
#include <stdlib.h>
#include <iostream>
#include "math_tools.h"

#define INF (1E9)

#define MAX(_A, _B) (_A < _B ? _B : _A)
#define MIN(_A, _B) (_A < _B ? _A : _B)

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

    std::cout << "Creating biomes" << std::endl;
    numBiomes = 8;
    biomes = (Biome**) malloc(numBiomes * sizeof(Biome*));

    biomes[0] = new Biome(0x0000FF, -100); // Ocean
    biomes[1] = new Biome(0x00FF00, 0); // Ground

}
World::~World()
{
    free(valMap);
    for (int i = 0; i < numLayers; ++i)
    {
        free(gridLayers[i]);
    }
    free(gridLayers);

    for (int i = 0; i < numBiomes; ++i)
    {
        free(biomes[i]);
    }
    free(biomes);
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
    int total = height * width;
    int c = 0;
    int nextP = 10;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Show how far it is through the generation process
            ++c;
            int perc = 100.0 * c / total;
            if (perc == nextP)
            {
                std::cout << perc << "%" << std::endl;
                nextP += 10;
            }
            float h = 0;
            for (int i = 0; i < numLayers; ++i)
            {
                h += gridLayers[i]->getVal(x, y) * (gridLayers[i]->getScale() / START_SCALE);
            }
            setVal(h, x, y);
        }
    }
    establishBounds();
}

void World::establishBounds()
{
    maxV = -1 * INF;
    minV = INF;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            maxV = MAX(maxV, getVal(x, y));
            minV = MIN(minV, getVal(x, y));
        }
    }

    std::cout << "(MAX, MIN) = (" << maxV << ", " << minV << ")" << std::endl;
}

void World::setColourMode(int m)
{
    colourMode = m;
}

unsigned int World::getColour(int x, int y)
{
    float v = getVal(x, y);
    if (colourMode == 1)
    {
        unsigned int c = 0;
        for (int i = 0; i < numBiomes; ++i)
        {
            if (biomes[i] == NULL || biomes[i]->startH > v)
            {
                break;
            }
            c = biomes[i]->colour;
        }
        return c;
    }
    else if (colourMode == 2)
    {
        // Return grey-scale colour
        unsigned int c = 256.0 * (v - minV) / (maxV - minV);
        return c * 0x010101;
    }
}



Biome::Biome(unsigned int _colour, float _startH)
{
    colour = _colour;
    startH = _startH;
}