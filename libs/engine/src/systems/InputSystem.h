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

#ifdef _DEBUG
	#undef main
#endif

class ENGINE_API S_InputSystem :
	public SkaiaCore::System
{
    private:
        SkaiaCore::Coordinator* coordinator;
    public:
        S_InputSystem(SkaiaCore::Coordinator* c);
        void Update() override;
        void Render() override;
        void Cleanup() override;
        void Initialize(void* data = nullptr) override;
        bool HandleInput(SDL_Event ev);
};