/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "systems/RenderSystem.h"
#include <iostream>

#ifdef _DEBUG
	#undef main
#endif

S_RenderSystem::S_RenderSystem(SkaiaCore::Coordinator* c) {
	coordinator = c;

    Signature signature;
    signature.set(coordinator->GetComponentType<S_Transform>());
	signature.set(coordinator->GetComponentType<S_Sprite>());
	coordinator->SetSystemSignature<S_RenderSystem>(signature);
}

void S_RenderSystem::Initialize(void* data)
{
    pRenderer = (SDL_Renderer*)data;

	std::cout << "Render System Initalized" << "\n";
}

void S_RenderSystem::Render()
{
    SDL_RenderPresent(pRenderer);
}

void S_RenderSystem::Update() {
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(pRenderer);

    for (auto const& entity : mEntities)
	{
        auto& entityS_Transform = coordinator->GetComponent<S_Transform>(entity);
        auto& entityS_Sprite = coordinator->GetComponent<S_Sprite>(entity);

        if (entityS_Sprite.color.r == -1)
        {
            // do nothing
        } else {
            SDL_Rect fillRect = { entityS_Transform.x, entityS_Transform.y, entityS_Transform.width, entityS_Transform.height };
            SDL_SetRenderDrawColor(pRenderer, entityS_Sprite.color.r, entityS_Sprite.color.g, entityS_Sprite.color.b, entityS_Sprite.color.a*255);
            SDL_RenderFillRect(pRenderer, &fillRect);
        }
	}
}

void S_RenderSystem::Cleanup()
{
	// nothing to implement here
}
	