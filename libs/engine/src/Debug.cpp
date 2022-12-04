#pragma once

#include <SDL.h>
#include "Debug.h"
#include "Input.h"
#include <iostream>
#undef main

DebugSystem::DebugSystem(SkaiaCore::Coordinator* c) {
	coordinator = c;
}

void DebugSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator->GetComponentType<Debug>());
	coordinator->SetSystemSignature<DebugSystem>(signature);
	std::cout << "Debug System Initalized" << "\n";
}

void DebugSystem::Render()
{
	// nothing to implement here
}

void DebugSystem::Update() {
	for (auto const& entity : mEntities)
	{
		auto& entityInputComponent = coordinator->GetComponent<Input>(entity);
		if (entityInputComponent.UP_PRESSED)
		{
			std::cout << "up is pressed" << "\n";
		}
	}
}

void DebugSystem::Cleanup()
{
	// nothing to implement here
}
	