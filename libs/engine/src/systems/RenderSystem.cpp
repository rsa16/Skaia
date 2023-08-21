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

namespace Skaia
{
    namespace Systems
    {
        RenderSystem::RenderSystem(Skaia::Core::Coordinator* c) {
            coordinator = c;

            Signature signature;
            signature.set(coordinator->GetComponentType<Components::Transform>());
            signature.set(coordinator->GetComponentType<Components::Sprite>());
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
                auto& entityTransform = coordinator->GetComponent<Components::Transform>(entity);
                auto& entitySprite = coordinator->GetComponent<Components::Sprite>(entity);

                if (entitySprite.color.r == -1)
                {
                    entitySprite.tex->SetAlpha(entitySprite.color.a*255);
                    entitySprite.tex->Render(entityTransform.x, entityTransform.y);
                    // do nothing
                } else {
                    if (entity == 2)
                    {
                        // printf("x: %d,  y: %d, width: %d, height: %d\n", entityTransform.x, entityTransform.y, entityTransform.width, entityTransform.height);
                    }
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
    }
}