/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "Input.h"
#include <iostream>
#undef main

InputSystem::InputSystem(SkaiaCore::Coordinator* c)
{
	coordinator = c;
}

void InputSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator->GetComponentType<Input>());
	coordinator->SetSystemSignature<InputSystem>(signature);
}

void InputSystem::Update()
{
	// nothing to do here
}

void InputSystem::Render()
{
	// nothing to do here
}

void InputSystem::Cleanup()
{
	// nothing to do here
}

bool InputSystem::HandleInput(SDL_Event ev)
{
	for (auto const& entity : mEntities)
	{
		auto& entityInputComponent = coordinator->GetComponent<Input>(entity);
		entityInputComponent.UP_PRESSED = (ev.type == entityInputComponent.KEYDOWN_EVENT && ev.key.keysym.sym == entityInputComponent.UP);
		entityInputComponent.DOWN_PRESSED = (ev.type == entityInputComponent.KEYDOWN_EVENT && ev.key.keysym.sym == entityInputComponent.DOWN);
		entityInputComponent.LEFT_PRESSED = (ev.type == entityInputComponent.KEYDOWN_EVENT && ev.key.keysym.sym == entityInputComponent.LEFT);
		entityInputComponent.RIGHT_PRESSED = (ev.type == entityInputComponent.KEYDOWN_EVENT && ev.key.keysym.sym == entityInputComponent.RIGHT);
	}
	return true;
}