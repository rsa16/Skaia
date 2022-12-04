/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "Core.h"
#include "SDL.h"
#undef main

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

struct ENGINE_API Window {
	const char* title;
	int width;
	int height;
	SDL_Renderer* pRenderer = nullptr;
	SDL_Window* pWindow = nullptr;
};

class ENGINE_API WindowSystem :
	public SkaiaCore::System
{
private:
	SkaiaCore::Coordinator* coordinator;
public:
	WindowSystem(SkaiaCore::Coordinator* c);
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void Initialize() override;
};