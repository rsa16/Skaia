/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "systems/InputSystem.h"
#include <iostream>

#ifdef _DEBUG
	#undef main
#endif

S_InputSystem::S_InputSystem(SkaiaCore::Coordinator* c)
{
	coordinator = c;

    Signature signature;
	signature.set(coordinator->GetComponentType<S_Input>());
	coordinator->SetSystemSignature<S_InputSystem>(signature);
}

void S_InputSystem::Initialize(void* data)
{
    std::cout << "S_Input System Initialized" << "\n";
}

void S_InputSystem::Update()
{
	// nothing to do here
}

void S_InputSystem::Render()
{
	// nothing to do here
}

void S_InputSystem::Cleanup()
{
	// nothing to do here
}

bool S_InputSystem::HandleInput(SDL_Event ev)
{
	for (auto const& entity : mEntities)
	{
		auto& entityInputComponent = coordinator->GetComponent<S_Input>(entity);

        if (ev.type == entityInputComponent.KEYDOWN_EVENT)
        {
            entityInputComponent.UP_PRESSED = (ev.key.keysym.sym == entityInputComponent.UP ? true : entityInputComponent.UP_PRESSED);
            entityInputComponent.DOWN_PRESSED = (ev.key.keysym.sym == entityInputComponent.DOWN ? true : entityInputComponent.DOWN_PRESSED);
            entityInputComponent.LEFT_PRESSED = (ev.key.keysym.sym == entityInputComponent.LEFT ? true : entityInputComponent.LEFT_PRESSED);
            entityInputComponent.RIGHT_PRESSED = (ev.key.keysym.sym == entityInputComponent.RIGHT ? true : entityInputComponent.RIGHT_PRESSED);

        } else if (ev.type == entityInputComponent.KEYUP_EVENT)
        {
            entityInputComponent.UP_PRESSED = (ev.key.keysym.sym == entityInputComponent.UP ? false : entityInputComponent.UP_PRESSED);
            entityInputComponent.DOWN_PRESSED = (ev.key.keysym.sym == entityInputComponent.DOWN ? false : entityInputComponent.DOWN_PRESSED);
            entityInputComponent.LEFT_PRESSED = (ev.key.keysym.sym == entityInputComponent.LEFT ? false : entityInputComponent.LEFT_PRESSED);
            entityInputComponent.RIGHT_PRESSED = (ev.key.keysym.sym == entityInputComponent.RIGHT ? false : entityInputComponent.RIGHT_PRESSED);
        }
	}
	return true;
}