/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"
#include "box2d/box2d.h"
#include "SDL.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Physics
    {
        enum RigidBodyType
        {
            STATIC,
            DYNAMIC
        };
    }

    namespace Components
    {
        struct ENGINE_API RigidBody {
            Physics::RigidBodyType bodyType;
            float friction;
            float density = 1.0f;
            b2Body* box2dbody = nullptr;
        };
    }
}