#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "perlin.h"

using namespace std;

void log(const string msg);
int getRand(int lower, int upper);
void writePixelData(SDL_Surface *image);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* const SCREEN_CAPTION = "MAP GEN";

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
SDL_Surface *image = NULL;
SDL_Texture *texture = NULL;

PerlinGrid* pg = NULL;

int main(void) 
{
    log("Program started");
    srand(0);

    log("Initialising SDL objects");
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, SCREEN_CAPTION);

    image = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    
    // Create Perlin noise object
    log("Creating PerlinGrid");
    pg = new PerlinGrid(128);
    
    writePixelData(image);

    texture = SDL_CreateTextureFromSurface(renderer, image);

    log("Starting GUI loop");
    bool running = true;
    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        } 

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // Free assets
    log("Freeing assets");
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(pg);

    log("Program ended");
    return EXIT_SUCCESS;
}

void log(const string msg)
{
    cout << msg << endl;
}

void writePixelData(SDL_Surface *image)
{
    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            unsigned char* pixels = (unsigned char*) image->pixels;
            int c = 128 + 128 * pg->getVal(x, y);//luRand(0, 256);
            pixels[ 4 * (y * image->w + x) + 0 ] = c;
            pixels[ 4 * (y * image->w + x) + 1 ] = c;
            pixels[ 4 * (y * image->w + x) + 2 ] = c;
            pixels[ 4 * (y * image->w + x) + 3 ] = 255;
        }
    }
}