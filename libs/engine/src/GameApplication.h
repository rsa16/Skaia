/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include <map>
#include <SDL.h>
#include <iostream>
#include <vector>
#include "SkaiaCore.h"

// default systems
#include "systems/DebugSystem.h"
#include "systems/WindowSystem.h"
#include "systems/InputSystem.h"
#include "systems/RenderSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/AudioSystem.h"

#include "behaviors/SkaiaEvents.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia {
	class ENGINE_API GameApplication
	{
		private:
			Skaia::Events::Event* ev;
			SDL_Renderer* pRenderer;
			Skaia::Core::Coordinator* coordinator;

			bool fpsCounter = false;

		public:
			std::unordered_map<std::type_index, std::shared_ptr<Skaia::Core::System>> mSystems;
			
			GameApplication(Skaia::Core::Coordinator* c, const char* title, int width, int height, bool fullscreen = false);

			void Initialize();
			void Render();
			void Update();
			void Cleanup();

			void SetCounterOn() { fpsCounter = true; }
			void SetCounterOff() { fpsCounter = false; }

			void Start(int FPSLOCK=61);

			SDL_Renderer* GetRenderer() { return pRenderer; };

			template<typename T>
			void TrackSystem()
			{
				auto system = coordinator->RegisterSystem<T>();
				mSystems.insert(std::make_pair(std::type_index(typeid(T)), system));
			}

			template<typename T>
			std::shared_ptr<T> GetSystem()
			{
				return std::static_pointer_cast<T>(mSystems[std::type_index(typeid(T))]);
			}

			bool HandleEvents();
	};
}