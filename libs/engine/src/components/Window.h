#pragma once

#include "SkaiaCore.h"
#include "SDL.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
	namespace Components
	{
		struct ENGINE_API Window {
			SDL_Window* pWindow = nullptr;
		};
	}
}
