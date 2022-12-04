#include "SkaiaImaging.h"

Texture::Texture()
{
    
}
Image::Image(SDL_Renderer* renderer, const char* path)
{
    mTexture = IMG_LoadTexture(renderer, path);
    pRenderer = renderer;
}