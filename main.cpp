#include <iostream>
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include "world.h"
#include <time.h>

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

World* world = NULL;

long long WORLD_SEED = time(NULL);
int NUM_NOISE_LAYERS = 8;

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
    
    // Create World object
    log("Creating World");
    world = new World(SCREEN_WIDTH, SCREEN_HEIGHT, NUM_NOISE_LAYERS, WORLD_SEED);

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
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_1)
                {
                    world->setColourMode(1);
                    writePixelData(image);
                    texture = SDL_CreateTextureFromSurface(renderer, image);
                }
                else if (event.key.keysym.sym == SDLK_2)
                {
                    world->setColourMode(2);
                    writePixelData(image);
                    texture = SDL_CreateTextureFromSurface(renderer, image);
                }
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

    free(world);

    log("Program ended");
    return EXIT_SUCCESS;
}

void log(const string msg)
{
    cout << msg << endl;
}

void writePixelData(SDL_Surface *image)
{
    log("Writing pixel data");
    
    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            
            unsigned char* pixels = (unsigned char*) image->pixels;
            unsigned int c = world->getColour(x, y);
            int r = (c & 0xFF0000) >> 16;
            int g = (c & 0x00FF00) >> 8;
            int b = (c & 0x0000FF) >> 0;
            int a = 255;
            
            pixels[ 4 * (y * image->w + x) + 0 ] = b;
            pixels[ 4 * (y * image->w + x) + 1 ] = g;
            pixels[ 4 * (y * image->w + x) + 2 ] = r; 
            pixels[ 4 * (y * image->w + x) + 3 ] = c;
        }
    }
}