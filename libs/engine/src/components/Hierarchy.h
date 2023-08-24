/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Components
    {
        struct ENGINE_API Hierarchy {
            std::size_t children{};
            
            Entity first = null;
            Entity previous Entity::Null;
            Entity next = Entity::Null;
            
            Entity parent = Entity::Null;
        };
    }
}