/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"

#include "components/Input.h"
#include "components/Debug.h"

#ifdef _DEBUG
	#undef main
#endif

class ENGINE_API S_DebugSystem : public SkaiaCore::System 
{
    private:
        SkaiaCore::Coordinator* coordinator;
    public:
        S_DebugSystem(SkaiaCore::Coordinator* coordinator);
        void Update() override;
        void Render() override;
        void Cleanup() override;
        void Initialize(void* data = nullptr) override;
};