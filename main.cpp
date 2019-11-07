#include <iostream>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

void log(const string msg);
int getRand(int lower, int upper);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* const SCREEN_CAPTION = "MAP GEN";

SDL_Renderer *renderer;
SDL_Window *window;

int main(void) 
{
    log("Program started");
    srand(0);

    log("Initialising SDL objects");
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, SCREEN_CAPTION);

    log("Starting GUI loop");
    bool running = true;
    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        for (int y = 0; y < SCREEN_HEIGHT; ++y)
        {
            for (int x = 0; x < SCREEN_WIDTH; ++x)
            {
                SDL_SetRenderDrawColor(renderer, x % 256, y % 256, (x + y) % 256, 0);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        } 

        SDL_RenderPresent(renderer);
    }

    // Free assets
    log("Freeing assets");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    log("Program ended");
    return EXIT_SUCCESS;
}

void log(const string msg)
{
    cout << msg << endl;
}

int getRand(int lower, int upper)
{
    // return a random number in the range [lower, upper)
    int r = rand();
    return lower + r % (upper - lower);
}