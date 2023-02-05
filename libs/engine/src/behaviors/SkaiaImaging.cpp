#include "SkaiaImaging.h"
#include <iostream>

#ifdef _DEBUG
	#undef main
#endif

/// @brief Initialize texture class.
/// @param pr Texture class requires SDL_Renderer to be able to renderer. TODO: Wrap renderer around somehow
S_Texture::S_Texture(SDL_Renderer* pr)
{
    pRenderer = pr;

    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

S_Texture::~S_Texture()
{
    Free();
}

/// @brief Load texture from an image file.
/// @param filePath Path to an image format that has been initialized already. TODO: wrap that around
/// @return Success or failiure
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

/// @brief Render the texture onto the screen
/// @param x x-coordinate
/// @param y y-coordinate
void S_Texture::Render(int x, int y)
{
    SDL_Rect renderRect = { x, y, mWidth, mHeight };
    SDL_RenderCopy(pRenderer, mTexture, NULL, &renderRect);
}

int S_Texture::GetWidth() { return mWidth; } // Get width
int S_Texture::GetHeight() {return mHeight; } // Get height

void S_Texture::SetWidth(int width) { mWidth = width; }
void S_Texture::SetHeight(int height) { mHeight = height; }

/// @brief Load an SDL texture into S_Teture
/// @param tex the said SDL texture
/// @return Success or failiure
bool S_Texture::LoadSDLTex(SDL_Texture* tex)
{
    Free();
    
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

namespace SkaiaTypeset
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
        loadedFonts.insert({fontPath.substr(0, fontPath.find(".ttf")), font});
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

    bool Font::RenderText(SDL_Renderer* pr, std::string text, S_Texture* texture, S_Color color)
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
            } else {
                texture->SetWidth(surf->w);
                texture->SetHeight(surf->h);
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
        mTexture = new S_Texture(pRenderer);
        mColor = {255, 255, 255};
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

    void Text::SetColor(S_Color color)
    {
        mColor = color;
    }

    void Text::Render(int x, int y)
    {
        mTexture->Render(x, y);
    }
}