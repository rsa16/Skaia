/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "Types.h"
#include "SkaiaCore.h"
#include "SDL.h"
#include <unordered_map>

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Collision
    {
        enum class State
        {
            ON_TOP = 1,
            ON_BOTTOM = 2,
            ON_LEFT = 3,
            ON_RIGHT = 4,
        };

        struct Box
        {
            float top;
            float bottom;
            float left;
            float right;
        };
    };

    namespace Components
    {
        struct ENGINE_API Collider
        {
            Collision::Box boundingBox;
            std::string collisionTag = "default";

            std::unordered_map<Collision::State, Collider*> collisions = {};
            bool isCurrentlyColliding = false;
            Entity owner = NullEntity;
        };

        inline bool operator==(const Collider& lhs, const Collider& rhs)
        {
            return lhs.owner == rhs.owner;
        }
    };
}