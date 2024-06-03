/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"

#include "components/Sprite.h"
#include "components/Transform.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace UI
    {
        // SDL_Texture* UITexture;
    }

    namespace Systems
    {
        class ENGINE_API RenderSystem : 
            public Skaia::Core::System 
        {
            private:
                Skaia::Core::Coordinator* coordinator;
                SDL_Renderer* pRenderer;
                SDL_Texture* displayTex;
                SDL_Rect displayRect;

            public:
                RenderSystem(Skaia::Core::Coordinator* coordinator);
                void Update() override;
                void Render() override;
                void Cleanup() override;
                void Initialize(void* data = nullptr) override;
                void HandleUserEvent(void* data = nullptr) override {};
        };
    }
}