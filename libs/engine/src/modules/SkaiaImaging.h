/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Types.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Imaging
    {
        //////////////////////////////////////////////////
        // OTHER STUFF
        //////////////////////////////////////////////////

        struct ENGINE_API Color {
            float r, g, b;
            float a = 1.0;
        };

        class ENGINE_API Texture 
        {
            private:
                SDL_Texture* mTexture;
                SDL_Renderer* pRenderer;

                int mWidth;
                int mHeight;

            public:
                Texture(SDL_Renderer* pr);
                ~Texture();

                bool LoadSDLTex(SDL_Texture* tex);
                bool LoadFile(std::string filePath);

                // deallocate texture
                void Free();

                // render at coordinate
                void Render(int x, int y);

                // image dimensions
                int GetWidth();
                int GetHeight();

                void SetWidth(int width);
                void SetHeight(int height);

                void SetAlpha(Uint8 alpha);
        };

        //////////////////////////////////////////////////
        // IMAGE STUFF
        //////////////////////////////////////////////////

        class ENGINE_API Image 
        {
            private:
                SDL_Texture* mTexture;
                SDL_Renderer* pRenderer;

            public:
                Image(SDL_Renderer* pRenderer, const char* imagePath = nullptr);

                void Save(const char* fileName);
                Texture AsTexture();
                static Image Load(const char* imagePath);
                static void Save(SDL_Surface surf, const char* fileName);
        };
    }
}