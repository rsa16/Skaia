#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Types.h"
#include <SDL_ttf.h>
#include <unordered_map>

#ifdef _DEBUG
	#undef main
#endif

//////////////////////////////////////////////////
// OTHER STUFF
//////////////////////////////////////////////////

struct ENGINE_API S_Color {
    float r, g, b;
    float a = 1.0;
};

class ENGINE_API S_Texture 
{
    private:
        SDL_Texture* mTexture;
        SDL_Renderer* pRenderer;

        int mWidth;
        int mHeight;

    public:
        S_Texture(SDL_Renderer* pr);
        ~S_Texture();

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

};

//////////////////////////////////////////////////
// IMAGE STUFF
//////////////////////////////////////////////////

class ENGINE_API S_Image 
{
    private:
        SDL_Texture* mTexture;
        SDL_Renderer* pRenderer;

    public:
        S_Image(SDL_Renderer* pRenderer, const char* imagePath = nullptr);

        void Save(const char* fileName);
        S_Texture AsTexture();
        static S_Image Load(const char* imagePath);
        static void Save(SDL_Surface surf, const char* fileName);
};

//////////////////////////////////////////////////
// FONT STUFF
//////////////////////////////////////////////////

// Font styles correspond to SDL_TTF styles because this is basically a
// high level wrapper

namespace SkaiaTypeset {
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
            
            bool RenderText(SDL_Renderer* pr, std::string text, S_Texture* texture, S_Color color={255, 255, 255});

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
            S_Texture* mTexture;
            Font mFont;
            S_Color mColor;
            SDL_Renderer* pRenderer;
            std::string mText;

        public:
            Text(SDL_Renderer* pRenderer, FontDatabase fontDB, std::string fontName);
            
            void SetText(std::string str);
            void SetFont(Font font);
            void SetSize(int fontSize);
            void SetColor(S_Color color);

            void Render(int x, int y);
    };
}