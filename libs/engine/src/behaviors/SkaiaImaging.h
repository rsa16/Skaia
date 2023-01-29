#include <SDL.h>
#include <SDL_image.h>
#include "Types.h"

#ifdef _DEBUG
	#undef main
#endif

struct Color {
    float r, g, b;
    float a = 1.0;
};

class ENGINE_API Texture {
private:
    SDL_Texture* mTexture;
public:
    Texture();
    void LoadSDLTex(SDL_Texture* tex);
};

class ENGINE_API Image {
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