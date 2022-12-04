/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/


#include "GameApplication.h"
#undef main

GameApplication::GameApplication(SkaiaCore::Coordinator* c, const char* title, int width, int height)
{
	coordinator = c;
	coordinator->Initialize();

	// register default components
	coordinator->RegisterComponent<Window>();
	coordinator->RegisterComponent<Input>();
	coordinator->RegisterComponent<Debug>();

	// register default systems
	TrackSystem<WindowSystem>();
	TrackSystem<InputSystem>();
	TrackSystem<DebugSystem>();

	Entity window = coordinator->CreateEntity();
	coordinator->AddComponent<Window>(window,
		Window{
			.title = title,
			.width = width,
			.height = height
		});
	coordinator->AddComponent<Input>(window, Input{});
	coordinator->AddComponent<Debug>(window, Debug{});
}

void GameApplication::Initialize()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Initialize();
	}
}

void GameApplication::Update()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Update();
	}
}

void GameApplication::Render()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Render();
	}
}

bool GameApplication::HandleEvents()
{
	// get input system  through an ugly pointer cast which unfortunately works
	std::shared_ptr<InputSystem> inputSystem = std::static_pointer_cast<InputSystem>(mSystems[std::type_index(typeid(InputSystem))]);
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

void GameApplication::Cleanup()
{
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->Cleanup();
	}
}