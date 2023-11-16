#include "iostream"
#include "SDL.h"
#include "SDL_image.h"
#include "Classes/DuckTexture.h"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
//SDL_Texture* gForegroundTexture = nullptr;
DuckTexture* gForegroundTexture = nullptr;
DuckTexture* gBackgroundTexture = nullptr;

bool Init();
void Close();


SDL_Texture *LoadTexture(const char *path);

int main(int argv, char** args)
{
    bool applicationQuit = false;
    SDL_Event e;

    Init();

    gForegroundTexture = new DuckTexture();
    gForegroundTexture->LoadFromFile("images/textures/foo.png", gRenderer);

    gBackgroundTexture = new DuckTexture();
    gBackgroundTexture->LoadFromFile("images/textures/background.png", gRenderer);

    while (!applicationQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                applicationQuit = true;
            }
        }

        // Rendering rects
        /*
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0XFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_Rect redRect { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &redRect);

        SDL_Rect greenRect { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &greenRect);

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < SCREEN_HEIGHT; ++i)
        {
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
        }


        SDL_Rect topViewPort;
        topViewPort.x = 0;
        topViewPort.y = 0;
        topViewPort.h = SCREEN_HEIGHT / 2;
        topViewPort.w = SCREEN_WIDTH;
        SDL_RenderSetViewport(gRenderer, &topViewPort);
        SDL_RenderCopy(gRenderer, gForegroundTexture, NULL, NULL);

         */

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        gBackgroundTexture->RenderAtScreenPoint(0,0, gRenderer);
        gForegroundTexture->RenderAtScreenPoint(240, 190, gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    Close();
    return 0;
}

bool Init()
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
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr)
            {
                printf("SDL renderer couldn't be created. Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image couldn't initialize. Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }

        return success;
    }
    return success;
}


SDL_Texture *LoadTexture(const char *path)
{
    SDL_Texture* createdTexture = nullptr;
    SDL_Surface* surfaceForTexture = IMG_Load(path);
    if (surfaceForTexture == nullptr)
    {
        printf("Couldn't load texture for surface from path %s Error: %s", path, IMG_GetError());
    }
    else
    {
        createdTexture = SDL_CreateTextureFromSurface(gRenderer, surfaceForTexture);
        if (createdTexture == nullptr)
        {
            printf("Couldn't create texture from surface %s. Error: %s", path, SDL_GetError());
        }

        SDL_FreeSurface(surfaceForTexture);
        return createdTexture;
    }
}



void Close()
{
    gForegroundTexture->Free();
    gBackgroundTexture->Free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}
