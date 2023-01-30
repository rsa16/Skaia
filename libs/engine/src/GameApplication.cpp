/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/


#include "GameApplication.h"
#include "behaviors/SkaiaTimer.h"
#include <string>

#ifdef _DEBUG
	#undef main
#endif

S_GameApplication::S_GameApplication(SkaiaCore::Coordinator* c, const char* title, int width, int height)
{
	coordinator = c;
	coordinator->Initialize();

	// register default components
	coordinator->RegisterComponent<S_Window>();
	coordinator->RegisterComponent<S_Input>();
	coordinator->RegisterComponent<S_Debug>();
	coordinator->RegisterComponent<S_Transform>();
	coordinator->RegisterComponent<S_Sprite>();

	// register default systems
	TrackSystem<S_WindowSystem>();
	TrackSystem<S_InputSystem>();
	TrackSystem<S_DebugSystem>();
	TrackSystem<S_RenderSystem>();

	// sdl init stuff
	SDL_Window* pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	S_Entity window = coordinator->CreateEntity();
	coordinator->AddComponent<S_Window>(window,
		S_Window{
			.pWindow = pWindow
		});
	coordinator->AddComponent<S_Input>(window, S_Input{});
	coordinator->AddComponent<S_Debug>(window, S_Debug{});
}

void S_GameApplication::Start(int FPSLOCK)
{
	int frameDelay = 1000 / FPSLOCK;
	Uint32 frameStart;
	int frameTime;

	S_Timer capTimer;
	S_Timer fpsTimer;

	//Start counting frames per second
	float countedFrames = 0;
	fpsTimer.Start();

	while (HandleEvents())
	{
		//Calculate and correct fps
		float avgFPS = countedFrames / ( fpsTimer.GetTicks() / 1000.f );
		if( avgFPS > 2000000.0f )
		{
			avgFPS = 0;
		}
		
		std::cout << "Average fps: " << avgFPS << "\n";

		++countedFrames;
		frameStart = SDL_GetTicks();

		// update variables and stuff first then render to view
		Update();
		Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

void S_GameApplication::Initialize()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Initialize(pRenderer);
	}
}

void S_GameApplication::Update()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Update();
	}
}

void S_GameApplication::Render()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Render();
	}
}

bool S_GameApplication::HandleEvents()
{
	// get input system  through an ugly pointer cast which unfortunately works
	std::shared_ptr<S_InputSystem> inputSystem = std::static_pointer_cast<S_InputSystem>(mSystems[std::type_index(typeid(S_InputSystem))]);
	while (SDL_PollEvent(&ev) != 0)
	{
		switch (ev.type) {
			case SDL_QUIT:
				return false;

			case SDL_KEYDOWN:
				if (ev.key.keysym.sym == SDLK_ESCAPE)
				{
					return false;
				}
				inputSystem->HandleInput(ev);
				break;

			case SDL_KEYUP:
				inputSystem->HandleInput(ev);
				break;
		}
	}
	return true;
}

void S_GameApplication::Cleanup()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Cleanup();
	}
}