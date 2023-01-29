/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include <map>
#include <SDL.h>
#include "SkaiaCore.h"
#include <iostream>
#include <vector>

// default behaviors
#include "systems/DebugSystem.h"
#include "systems/WindowSystem.h"
#include "systems/InputSystem.h"
#include "systems/RenderSystem.h"

#ifdef _DEBUG
	#undef main
#endif

class ENGINE_API GameApplication
{
private:
	SDL_Event ev;
	SDL_Renderer* pRenderer;
	SkaiaCore::Coordinator* coordinator;

public:
	std::unordered_map<std::type_index, std::shared_ptr<SkaiaCore::System>> mSystems;
	
	GameApplication(SkaiaCore::Coordinator* c, const char* title, int width, int height);

	void Initialize();
	void Render();
	void Update();
	void Cleanup();

	void Start(int FPSLOCK=60);

	template<typename T>
	void TrackSystem()
	{
		auto system = coordinator->RegisterSystem<T>();
		mSystems.insert(std::make_pair(std::type_index(typeid(T)), system));
	}

	bool HandleEvents();
};

