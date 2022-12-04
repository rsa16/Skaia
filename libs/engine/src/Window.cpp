#include "Window.h"
#include <SDL.h>
#include <iostream>
#include <sstream>
#include <SDL_image.h>
#undef main

WindowSystem::WindowSystem(SkaiaCore::Coordinator* c)
{
	coordinator = c;
}

void WindowSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator->GetComponentType<Window>());
	coordinator->SetSystemSignature<WindowSystem>(signature);

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
		windowComp.pWindow = SDL_CreateWindow(windowComp.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowComp.width, windowComp.height, SDL_WINDOW_RESIZABLE);
		windowComp.pRenderer = SDL_CreateRenderer(windowComp.pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
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
		SDL_DestroyRenderer(windowComp.pRenderer);
		SDL_Quit();
	}
}