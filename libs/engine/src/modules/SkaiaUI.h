/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "SkaiaImaging.h"
#include <SDL_ttf.h>
#include <unordered_map>
#include "Types.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia 
{
    namespace UI
    {
        //////////////////////////////////////////////////
        // FONT STUFF
        //////////////////////////////////////////////////

        // Font styles correspond to SDL_TTF styles because this is basically a
        // high level wrapper
        
        enum FontStyle
        {
            NORMAL = 0x00,
            BOLD = 0x01,
            ITALIC = 0x02,
            UNDERLINE = 0x04,
            STRIKETHROUGH = 0x08
        };

        inline FontStyle operator |(FontStyle a, FontStyle b)
        {
            return static_cast<FontStyle>(static_cast<int>(a) | static_cast<int>(b));
        }

        // forward declarai
        class ENGINE_API Font;

        // A database so we could load fonts and reuse them 
        // without having to load them again
        class ENGINE_API FontDatabase
        {
            private:
                std::unordered_map<std::string, Font> loadedFonts;
            
            public:
                FontDatabase() {};

                Font LoadFont(std::string fontPath, int fontSize=12);
                Font GetFont(std::string fontName);
        };

        // The actual font class.
        class ENGINE_API Font
        {
            private:
                TTF_Font* mFont;
                FontStyle mStyle;
                int mFontSize;
                std::string fontName;

            public:
                Font() {};
                Font(FontDatabase fontDB, std::string fontName);
                Font(std::string fontPath, int fontSize=12);

                static Font FromDB(FontDatabase fontDB, std::string fontName);

                void LoadFont(std::string fontPath, int fontSize=12);
                
                bool RenderText(SDL_Renderer* pr, std::string text, Imaging::Texture* texture, Imaging::Color color={255});

                int GetFontSize();
                FontStyle GetFontStyle();

                bool SetFontSize(int fontSize);
                void SetFontStyle(FontStyle style);

                std::string GetName();
                TTF_Font* GetSDLFont();

                bool operator() (const Font& lhs, const Font& rhs) const
                {
                    return lhs.fontName < rhs.fontName; 
                }
        };

        // Will represent text
        class ENGINE_API Text
        {
            private:
                Imaging::Texture* mTexture;
                Font mFont;
                Imaging::Color mColor;
                SDL_Renderer* pRenderer;
                std::string mText;

            public:
                Text(SDL_Renderer* pRenderer, FontDatabase fontDB, std::string fontName);
                
                void SetText(std::string str);
                void SetFont(Font font);
                void SetSize(int fontSize);
                void SetColor(Imaging::Color color);

                void Render(int x, int y);
        };
    }
}