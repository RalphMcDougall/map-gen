#include "world.h"
#include <stdlib.h>

World::World(int _width, int _height)
{
    width = _width;
    height = _height;

    heightMap = (float*) malloc(width * height * sizeof(float));
}
World::~World()
{
    free(heightMap);
}