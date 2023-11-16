//
// Created by kiril on 2023-11-11.
//

#include <cstdio>
#include "DuckTexture.h"

DuckTexture::DuckTexture()
{
    textureInternal = nullptr;
    width = 0;
    height = 0;
}

DuckTexture::~DuckTexture()
{
    Free();
}

bool DuckTexture::LoadFromFile(const char *path, SDL_Renderer *renderer)
{
    Free();
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* surface = IMG_Load(path);
    if (surface == nullptr)
    {
        printf("There was an issue creating a surface from texture at path: %s. Error: %s", path, IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x00, 0XFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (newTexture == nullptr)
        {
            printf("Error while creating a texture from surface %s, %s", path, SDL_GetError());
        }
        else
        {
            width = surface->w;
            height = surface->h;
        }

        SDL_FreeSurface(surface);
    }

    textureInternal = newTexture;
    return textureInternal != nullptr;
}

void DuckTexture::Free()
{
    if (textureInternal != nullptr)
    {
        SDL_DestroyTexture(textureInternal);
        textureInternal = nullptr;
        width = 0;
        height = 0;
    }
}

void DuckTexture::RenderAtScreenPoint(int x, int y, SDL_Renderer *renderer, SDL_Rect* clipArea)
{
    SDL_Rect renderQuad = {x, y, width, height};

    if (clipArea != nullptr)
    {
        renderQuad.w = clipArea->w;
        renderQuad.h = clipArea->h;
    }

    SDL_RenderCopy(renderer, textureInternal, nullptr, &renderQuad);
}

int DuckTexture::GetWidth()
{
    return width;
}

int DuckTexture::GetHeight()
{
    return height;
}
