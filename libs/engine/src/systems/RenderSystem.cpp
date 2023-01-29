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

RenderSystem::RenderSystem(SkaiaCore::Coordinator* c) {
	coordinator = c;

    Signature signature;
    signature.set(coordinator->GetComponentType<Transform>());
	signature.set(coordinator->GetComponentType<Sprite>());
	coordinator->SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Initialize(void* data)
{
    pRenderer = (SDL_Renderer*)data;

	std::cout << "Render System Initalized" << "\n";
}

void RenderSystem::Render()
{
    SDL_RenderPresent(pRenderer);
}

void RenderSystem::Update() {
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(pRenderer);

    for (auto const& entity : mEntities)
	{
        auto& entityTransform = coordinator->GetComponent<Transform>(entity);
        auto& entitySprite = coordinator->GetComponent<Sprite>(entity);

        if (entitySprite.color.r == -1)
        {
            // do nothing
        } else {
            SDL_Rect fillRect = { entityTransform.x, entityTransform.y, entityTransform.width, entityTransform.height };
            SDL_SetRenderDrawColor(pRenderer, entitySprite.color.r, entitySprite.color.g, entitySprite.color.b, entitySprite.color.a*255);
            SDL_RenderFillRect(pRenderer, &fillRect);
        }
	}
}

void RenderSystem::Cleanup()
{
	// nothing to implement here
}
	