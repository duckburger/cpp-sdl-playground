#include "iostream"
#include "SDL.h"
#include "SDL_image.h"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gTexture = nullptr;

bool Init();
bool LoadMedia();
void Close();
SDL_Texture* LoadTexture(const std::string& path);


int main(int argv, char** args)
{
    bool applicationQuit = false;
    SDL_Event e;

    Init();
    LoadMedia();

    while (!applicationQuit)
    {
        // Running the game loop here

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                applicationQuit = true;
            }
        }

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);
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

bool LoadMedia()
{
    bool success = true;

    gTexture = LoadTexture("images/textures/texture.png");
    if (gTexture == nullptr)
    {
        printf("Failed to load texture!\n");
        success = false;
    }
    return success;
}

SDL_Texture *LoadTexture(const std::string &path)
{
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
    if (newTexture == nullptr)
    {
        printf("Couldn't create a texture from %s Error: %s\\n", path.c_str(), SDL_GetError());
    }

    return newTexture;
}

void Close()
{
    SDL_DestroyTexture(gTexture);
    gTexture = nullptr;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}
