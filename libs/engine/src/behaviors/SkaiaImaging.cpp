/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "SkaiaImaging.h"
#include <iostream>

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Imaging
    {
        /// @brief Initialize texture class.
        /// @param pr Texture class requires SDL_Renderer to be able to renderer. TODO: Wrap renderer around somehow
        Texture::Texture(SDL_Renderer* pr)
        {
            pRenderer = pr;

            mTexture = NULL;
            mWidth = 0;
            mHeight = 0;
        }

        Texture::~Texture()
        {
            Free();
        }

        /// @brief Load texture from an image file.
        /// @param filePath Path to an image format that has been initialized already. TODO: wrap that around
        /// @return Success or failure
        bool Texture::LoadFile(std::string filePath)
        {
            // Get rid of existing texture if exists
            Free();

            SDL_Texture* newTexture = NULL;

            SDL_Surface* loadedSurf = IMG_Load(filePath.c_str());
            if (loadedSurf == NULL)
            {
                printf("Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError());
            } else {
                newTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurf);
            }

            SetWidth(loadedSurf->w);
            SetHeight(loadedSurf->h);

            // Return success
            mTexture = newTexture;
            return mTexture != NULL;
        }

        void Texture::Free()
        {
            if (mTexture != NULL)
            {
                SDL_DestroyTexture(mTexture);
                mTexture = NULL;
                mWidth = 0;
                mHeight = 0;
            }
        }

        /// @brief Render the texture onto the screen
        /// @param x x-coordinate
        /// @param y y-coordinate
        void Texture::Render(int x, int y)
        {
            SDL_Rect renderRect = { x, y, mWidth, mHeight };
            SDL_RenderCopy(pRenderer, mTexture, NULL, &renderRect);
        }

        int Texture::GetWidth() { return mWidth; } // Get width
        int Texture::GetHeight() {return mHeight; } // Get height

        void Texture::SetWidth(int width) { mWidth = width; }
        void Texture::SetHeight(int height) { mHeight = height; }

        void Texture::SetAlpha(Uint8 alpha) {
            SDL_SetTextureBlendMode( mTexture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod( mTexture, alpha );
        }

        /// @brief Load an SDL texture into Teture
        /// @param tex the said SDL texture
        /// @return Success or failiure
        bool Texture::LoadSDLTex(SDL_Texture* tex)
        {
            Free();

            SDL_Point size;
            SDL_QueryTexture(tex, NULL, NULL, &size.x, &size.y);

            SetWidth(size.x);
            SetHeight(size.y);

            mTexture = tex;
            return mTexture != NULL || mTexture != nullptr; 
        }



        Image::Image(SDL_Renderer* renderer, const char* path)
        {
            mTexture = IMG_LoadTexture(renderer, path);
            pRenderer = renderer;
        }

        Texture Image::AsTexture()
        {
            Texture tex(pRenderer);
            tex.LoadSDLTex(mTexture);
            return tex;
        }
    }
}