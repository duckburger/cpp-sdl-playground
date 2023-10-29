#include "SDL.h"
#include <iostream>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gImageSurface = nullptr;

bool init();
bool loadMedia();
void close();

int main(int argv, char** args)
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else if (!loadMedia())
    {
        printf("Failed to load media!\n");
    }
    else
    {
        SDL_BlitSurface(gImageSurface, nullptr, gScreenSurface, nullptr);
        SDL_UpdateWindowSurface(gWindow);
        SDL_Event e;
        bool quit = false;
        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
    }
    close();
    return 0;
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Couldn't initialize! Error: %s\n", SDL_GetError());
    }
    else
    {
        gWindow = SDL_CreateWindow("Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            printf("SDL window couldn't be created. Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }

        return success;
    }
}

bool loadMedia()
{
    bool success = true;

    gImageSurface = SDL_LoadBMP("images/hello_world.bmp");
    if (gImageSurface == nullptr)
    {
        printf("SDL image couldn't be loaded. Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    SDL_FreeSurface(gImageSurface);
    gImageSurface = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}