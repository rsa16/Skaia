#pragma once
#include <map>
#include <SDL.h>
#include "Core.h"
#include <iostream>
#include <vector>

// default behaviors
#include "Debug.h"
#include "Window.h"
#include "Input.h"
#undef main

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif


class ENGINE_API GameApplication
{
private:
	SDL_Event ev;
	SkaiaCore::Coordinator* coordinator;
	std::unordered_map<std::type_index, std::shared_ptr<SkaiaCore::System>> mSystems;

public:
	GameApplication(SkaiaCore::Coordinator* c, const char* title, int width, int height);

	void Initialize();
	void Render();
	void Update();
	void Cleanup();

	template<typename T>
	void TrackSystem()
	{
		auto system = coordinator->RegisterSystem<T>();
		mSystems.insert({ std::type_index(typeid(T)), system });
	}

	bool HandleEvents();
};

