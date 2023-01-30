#include "SkaiaCore.h"
#include "SDL.h"

#ifdef _DEBUG
	#undef main
#endif

struct ENGINE_API S_Window {
	SDL_Window* pWindow = nullptr;
};