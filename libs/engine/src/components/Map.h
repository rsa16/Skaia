/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"
#include <string>

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Components
    {
        struct ENGINE_API Map {
            int tileSize;

            std::unordered_map<std::string, std::string> tilesetPaths;
            std::string mapPath;
        };
    }
}