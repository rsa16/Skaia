#include "SkaiaImaging.h"

#ifdef _DEBUG
	#undef main
#endif

S_Texture::S_Texture(SDL_Renderer* pr)
{
    pRenderer = pRenderer;

    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

S_Texture::~S_Texture()
{
    Free();
}

bool S_Texture::LoadFile(std::string filePath)
{
    // Get rid of existing texture if exists
    Free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurf = IMG_Load(filePath.c_str());
    if (loadedSurf == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
    } else {
        // Color key image
        SDL_SetColorKey(loadedSurf, SDL_TRUE, SDL_MapRGB( loadedSurf->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurf);
    }

    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void S_Texture::Free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void S_Texture::Render(int x, int y)
{

}

bool S_Texture::LoadSDLTex(SDL_Texture* tex)
{
    mTexture = tex;
    return mTexture != NULL || mTexture != nullptr; 
}

S_Image::S_Image(SDL_Renderer* renderer, const char* path)
{
    mTexture = IMG_LoadTexture(renderer, path);
    pRenderer = renderer;
}

S_Texture S_Image::AsTexture()
{
    S_Texture tex(pRenderer);
    tex.LoadSDLTex(mTexture);
    return tex;
}