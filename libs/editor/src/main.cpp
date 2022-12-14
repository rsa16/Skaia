/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "GameApplication.h"
#include "SDL.h"
#include "SDL_Image.h"
#include <sstream>
#undef main

SkaiaCore::Coordinator coordinator;

const int FPSLOCK = 60;
const int frameDelay = 1000 / FPSLOCK;

int main()
{	
	Uint32 frameStart;
	int frameTime;

	GameApplication* game = new GameApplication(&coordinator, "Farming Sim", 500, 600);
	
	// initialize
	game->Initialize();

	while (game->HandleEvents())
	{
		frameStart = SDL_GetTicks();

		game->Render();
		game->Update();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return 0;
}