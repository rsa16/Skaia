/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/


#include "GameApplication.h"
#include <string>

// behaviors
#include "behaviors/SkaiaUI.h"
#include "behaviors/SkaiaTimer.h"
#include "behaviors/SkaiaAudio.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
	GameApplication::GameApplication(Skaia::Core::Coordinator* c, const char* title, int width, int height, bool fullscreen)
	{
		coordinator = c;
		coordinator->Initialize();

		// register default components
		coordinator->RegisterComponent<Components::Window>();
		coordinator->RegisterComponent<Components::Input>();
		coordinator->RegisterComponent<Components::Debug>();
		coordinator->RegisterComponent<Components::Transform>();
		coordinator->RegisterComponent<Components::Sprite>();
		coordinator->RegisterComponent<Components::RigidBody>();
		coordinator->RegisterComponent<Components::AudioSource>();

		// register default systems
		TrackSystem<Systems::WindowSystem>();
		TrackSystem<Systems::InputSystem>();
		TrackSystem<Systems::DebugSystem>();
		TrackSystem<Systems::PhysicsSystem>();
		TrackSystem<Systems::RenderSystem>();
		TrackSystem<Systems::AudioSystem>();

		// sdl init stuff
		SDL_Window* pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
		pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

		if (fullscreen)
		{
			SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			SDL_ShowCursor(false);
		}

		Skaia::Entity window = coordinator->CreateEntity(); 
		coordinator->AddComponent<Components::Window>(window,
			Components::Window{
				.pWindow = pWindow
			});
		coordinator->AddComponent<Components::Input>(window, Components::Input{});
		coordinator->AddComponent<Components::Debug>(window, Components::Debug{});
	}

	void GameApplication::Start(int FPSLOCK )
	{
		Skaia::UI::FontDatabase fontDB;
		Skaia::UI::Text* text;

		fontDB.LoadFont("data/fonts/roboto.ttf");
		text = new Skaia::UI::Text(pRenderer, fontDB, "roboto");

		int frameDelay = 1000 / FPSLOCK;
		Uint32 frameStart;
		int frameTime;

		Skaia::Timers::Timer capTimer;
		Skaia::Timers::Timer fpsTimer;

		// Start counting frames per second
		float countedFrames = 0;
		fpsTimer.Start();

		text->SetText("0");
		text->SetSize(14);

		Initialize();

		while (HandleEvents())
		{
			// Calculate and correct fps
			float avgFPS = countedFrames / ( fpsTimer.GetTicks() / 1000.f );
			if( avgFPS > 2000000.0f )
			{
				avgFPS = 0;
			}

			++countedFrames;
			frameStart = SDL_GetTicks();

			if (fpsCounter)
			{
				text->SetText(std::to_string(avgFPS));
			}

			// update variables and stuff first then render to view
			Update();
			if (fpsCounter) text->Render(10, 10);
			Render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}
	}

	void GameApplication::Initialize()
	{
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;
			system->Initialize(pRenderer);
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
		std::shared_ptr<Systems::InputSystem> inputSystem = GetSystem<Systems::InputSystem>();
		std::shared_ptr<Systems::PhysicsSystem> physicsSystem = GetSystem<Systems::PhysicsSystem>();
		std::shared_ptr<Systems::AudioSystem> audioSystem = GetSystem<Systems::AudioSystem>();

		while (Events::CheckEvent(&ev) != -1)
		{
			switch (ev->name) 
			{
				case Events::EventNames::KEYBOARD_EVENT:
					inputSystem->HandleInput(ev);
					break;

				case Events::EventNames::QUIT_EVENT:
					return false;

				case Events::EventNames::AUDIO_EVENT:
					audioSystem->HandleEvent(ev);
					break;
				
				case Events::EventNames::PHYSICS_EVENT:
					physicsSystem->HandleEvent(ev);
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
}