#include <SDL.h>
#include <SDL_image.h>
#include "Types.h"

#ifdef _DEBUG
	#undef main
#endif

struct S_Color {
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

};

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