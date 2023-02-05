/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "systems/DebugSystem.h"
#include <iostream>

#ifdef _DEBUG
#undef main
#endif

S_DebugSystem::S_DebugSystem(SkaiaCore::Coordinator *c)
{
	coordinator = c;

	Signature signature;
	signature.set(coordinator->GetComponentType<S_Debug>());
	signature.set(coordinator->GetComponentType<S_Input>());
	coordinator->SetSystemSignature<S_DebugSystem>(signature);
}

void S_DebugSystem::Initialize(void *data)
{
	std::cout << "Debug System Initalized"
			  << "\n";
}

void S_DebugSystem::Render()
{
	// nothing to implement here
}

void S_DebugSystem::Update()
{
	for (auto const &entity : mEntities)
	{
		auto &entityInputComponent = coordinator->GetComponent<S_Input>(entity);
		if (entityInputComponent.UP_PRESSED)
		{
		}
	}
}

void S_DebugSystem::Cleanup()
{
	// nothing to implement here
}
