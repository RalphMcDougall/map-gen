#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

void log(const string msg);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const string WINDOW_CAPTION = "MAP GEN";

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

int main()
{
    log("Program started");

    log("Creating SDL objects");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Error in initialisation
        log("SDL could not be initialised!");
        cout << SDL_GetError() << endl;
        return 0;
    }

    window = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        log("Couldn't create window");
        cout << SDL_GetError() << endl;
        return 0;
    }
    log("Program closed");
    return 0;
}

void log(const string msg)
{
    cout << msg << endl;
}