//
// Created by kiril on 2023-11-11.
//

#ifndef CPP_SDL_PLAYGROUND_DUCKTEXTURE_H
#define CPP_SDL_PLAYGROUND_DUCKTEXTURE_H

#include "SDL.h"
#include "SDL_image.h"

class DuckTexture
{
public:
    DuckTexture();
    ~DuckTexture();


    bool LoadFromFile(const char* path, SDL_Renderer* renderer);
    void Free();
    void RenderAtScreenPoint(int x, int y, SDL_Renderer* renderer, SDL_Rect* clipArea = nullptr);
    int GetWidth();
    int GetHeight();

private:

    SDL_Texture* textureInternal;
    int width;
    int height;
};


#endif //CPP_SDL_PLAYGROUND_DUCKTEXTURE_H
