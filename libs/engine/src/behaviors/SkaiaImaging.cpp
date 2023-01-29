#include "SkaiaImaging.h"

#ifdef _DEBUG
	#undef main
#endif

Texture::Texture()
{
    
}

void Texture::LoadSDLTex(SDL_Texture* tex)
{
    mTexture = tex;
}

Image::Image(SDL_Renderer* renderer, const char* path)
{
    mTexture = IMG_LoadTexture(renderer, path);
    pRenderer = renderer;
}

Texture Image::AsTexture()
{
    Texture tex;
    tex.LoadSDLTex(mTexture);
    return tex;
}