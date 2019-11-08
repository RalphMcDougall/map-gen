#ifndef _WORLD
#define _WORLD 1

class World
{
    private:
    int width, height;
    float * heightMap;
    public:
    World(int width, int height);
    ~World();
};


#endif