/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

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
		struct ENGINE_API Input
		{
			SDL_EventType KEYUP_EVENT = SDL_KEYUP;
			SDL_EventType KEYDOWN_EVENT = SDL_KEYDOWN;

			SDL_KeyCode UP = SDLK_w;
			SDL_KeyCode DOWN = SDLK_s;
			SDL_KeyCode RIGHT = SDLK_d;
			SDL_KeyCode LEFT = SDLK_a;

			bool UP_PRESSED = false;
			bool DOWN_PRESSED = false;
			bool RIGHT_PRESSED = false;
			bool LEFT_PRESSED = false;
			bool ESCAPE_PRESSED = false;

			SDL_KeyCode ESCAPE = SDLK_ESCAPE;

			SDL_EventType QUIT = SDL_QUIT;
		};
	}
}