/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/
#include <SDL.h>
#include <iostream>
#include <sstream>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "systems/WindowSystem.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
	namespace Systems
	{
		WindowSystem::WindowSystem(Skaia::Core::Coordinator* c)
		{
			coordinator = c;

			Signature signature;
			signature.set(coordinator->GetComponentType<Components::Window>());
			coordinator->SetSystemSignature<WindowSystem>(signature);

			if (TTF_Init() == -1)
			{
				std::stringstream buffer;
				buffer << "Could not initialize SDL_ttf properly, here is the error: " << TTF_GetError();

				throw std::runtime_error(buffer.str());		
			}
		}

		void WindowSystem::Initialize(void* data)
		{
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
				std::stringstream buffer;
				buffer << "Could not initialize SDL properly, here is the error: " << SDL_GetError();

				throw std::runtime_error(buffer.str());
			}
			if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
				std::stringstream buffer;
				buffer << "Could not initialize SDL_image properly, here is the error: " << IMG_GetError();

				throw std::runtime_error(buffer.str());
			}

			std::cout << "Window System Initalized" << "\n";
		}

		void WindowSystem::Update()
		{
			// nothing to do here
		}

		void WindowSystem::Render()
		{
			// nothing to do here
		}

		void WindowSystem::Cleanup()
		{
			for (auto const& entity : mEntities)
			{
				auto const& windowComp = coordinator->GetComponent<Components::Window>(entity);

				SDL_DestroyWindow(windowComp.pWindow);

				// quit sdl subsystem things
				IMG_Quit();
				TTF_Quit();
				SDL_Quit();
			}
		}		
	}
}