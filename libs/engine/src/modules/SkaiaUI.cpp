/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "SkaiaUI.h"
#include <iostream>

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace UI
    {
        /// @brief Retrieve a font from the database
        /// @param fontName The name of the font
        /// @return An instance of S_Font
        Font FontDatabase::GetFont(std::string fontName)
        {
            return loadedFonts[fontName];
        }

        /// @brief Load font into font database
        /// @param fontPath Path to font ttf file
        /// @param fontSize Pre initialized size
        /// @return Instance of S_Font
        Font FontDatabase::LoadFont(std::string fontPath, int fontSize)
        {
            Font font = Font(fontPath, fontSize);
            
            std::string baseFileName = fontPath.substr(fontPath.find_last_of("/\\") + 1);
            std::string::size_type const p(baseFileName.find(".ttf"));
            std::string fileNoExtension = baseFileName.substr(0, p);

            loadedFonts.insert({fileNoExtension, font});
            return font;
        }

        TTF_Font* Font::GetSDLFont() { return mFont; } // Get sdl font
        FontStyle Font::GetFontStyle() { return mStyle; } // get font style
        int Font::GetFontSize() { return mFontSize; } // get font size

        /// @brief Initialize from TTF font file
        /// @param fontPath the path to the TTF file
        /// @param fontSize the initial font size
        Font::Font(std::string fontPath, int fontSize)
        {
            mStyle = FontStyle::NORMAL;
            mFontSize = fontSize;
            fontName = fontPath.substr(0, fontPath.find(".ttf"));

            // load font
            mFont = NULL;
            mFont = TTF_OpenFont(fontPath.c_str(), mFontSize);

            if (mFont == NULL || mFont == nullptr)
            {
                printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
            }
        }

        /// @brief Initialize font from already existing database
        /// @param fontDB Font database holding fonts
        /// @param fn the name of the font
        Font::Font(FontDatabase fontDB, std::string fn)
        {
            Font font = fontDB.GetFont(fontName);

            mFont = font.GetSDLFont();
            mFontSize = font.GetFontSize();
            mStyle = font.GetFontStyle();
            fontName = fn;

            // std::cout << "another breakpoint" << "\n";
        }

        Font Font::FromDB(FontDatabase fontDB, std::string fn)
        {
            return fontDB.GetFont(fn);
        }

        /// @brief Wrapper around the regular initialization.
        /// @param fontPath Path to the TTF font
        /// @param fontSize Pre-initialized size
        /// @return an instance of S_Font
        void Font::LoadFont(std::string fontPath, int fontSize)
        {
            mStyle = FontStyle::NORMAL;
            mFontSize = fontSize;
            fontName = fontPath.substr(0, fontPath.find(".ttf"));

            // load font
            mFont = NULL;
            mFont = TTF_OpenFont(fontPath.c_str(), mFontSize);
            if (mFont == NULL || mFont == nullptr)
            {
                printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
            }
        }

        /// @brief Wrapper around TTF_SetFontSize
        /// @param fontSize Set the font size of the font
        /// @return True on success, false on failure
        bool Font::SetFontSize(int fontSize)
        {
            return TTF_SetFontSize(mFont, fontSize) == 0;
        }

        /// @brief Wrapper around TTF_SetFontStyle
        /// @param style the S_FontStyle you would like, can be OR'ed
        void Font::SetFontStyle(FontStyle style)
        {
            mStyle = style;
            TTF_SetFontStyle(mFont, mStyle);
        }

        bool Font::RenderText(SDL_Renderer* pr, std::string text, Imaging::Texture* texture, Imaging::Color color)
        {
            // std::cout << "new breakpoint" << "\n";
            SDL_Surface* surf = TTF_RenderText_Blended(mFont, text.c_str(), {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b});    
            SDL_Texture* mTex = NULL;

            if (surf == NULL)
            {
                printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); 
            } else {
                mTex = SDL_CreateTextureFromSurface(pr, surf);
                if (mTex == NULL)
                {
                    printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                }
            }

            if (mTex != NULL)
            {
                texture->LoadSDLTex(mTex);
                texture->SetWidth(surf->w);
                texture->SetHeight(surf->h);

                SDL_FreeSurface(surf);
            }

            return mTex != NULL;
        }

        /// @brief Get the font name
        /// @return the font name
        std::string Font::GetName()
        {
            return fontName;
        }

        Text::Text(SDL_Renderer* pr, FontDatabase fontDB, std::string fontName)
        {
            // std::cout << "breakpoint bish" << "\n";

            mFont = Font::FromDB(fontDB, fontName);;
            pRenderer = pr;
            mTexture = new Imaging::Texture(pRenderer);
            mColor = {255};
        }

        void Text::SetFont(Font font)
        {
            mFont = font;
            mFont.RenderText(pRenderer, mText, mTexture, mColor);
        }

        void Text::SetSize(int fontSize)
        {
            mFont.SetFontSize(fontSize);
            mFont.RenderText(pRenderer, mText, mTexture, mColor);
        }

        void Text::SetText(std::string str)
        {
            mText = str;
            // std::cout << "test" << "\n";
            mFont.RenderText(pRenderer, mText, mTexture, mColor);
        }

        void Text::SetColor(Imaging::Color color)
        {
            mColor = color;
        }

        void Text::Render(int x, int y)
        {
            mTexture->Render(x, y);
        }

        FontDatabase fontDB;
    }
}