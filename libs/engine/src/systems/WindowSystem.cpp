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

#include "systems/WindowSystem.h"

#ifdef _DEBUG
	#undef main
#endif

WindowSystem::WindowSystem(SkaiaCore::Coordinator* c)
{
	coordinator = c;

    Signature signature;
	signature.set(coordinator->GetComponentType<Window>());
	coordinator->SetSystemSignature<WindowSystem>(signature);
}

void WindowSystem::Initialize(void* data)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream buffer;
		buffer << "Could not initialize SDL properly, here is the error: " << SDL_GetError();

		throw std::runtime_error(buffer.str());
	}
	if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
		std::stringstream buffer;
		buffer << IMG_GetError();

		throw std::runtime_error(buffer.str());
	}

	for (auto const& entity : mEntities)
	{
		auto& windowComp = coordinator->GetComponent<Window>(entity);
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
		auto const& windowComp = coordinator->GetComponent<Window>(entity);

		SDL_DestroyWindow(windowComp.pWindow);
		SDL_Quit();
	}
}