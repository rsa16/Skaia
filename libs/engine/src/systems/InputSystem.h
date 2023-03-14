/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"
#include "SDL.h"

#include "components/Input.h"
#include "behaviors/SkaiaEvents.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Systems
    {
        class ENGINE_API InputSystem :
            public Skaia::Core::System
        {
            private:
                Skaia::Core::Coordinator* coordinator;
            public:
                InputSystem(Skaia::Core::Coordinator* c);
                void Update() override;
                void Render() override;
                void Cleanup() override;
                void Initialize(void* data = nullptr) override;
                bool HandleInput(Events::Event* ev);
        };
    }
}