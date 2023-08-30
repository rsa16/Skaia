/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"
#include "SDL.h"
#include "modules/SkaiaImaging.h"

#ifdef _DEBUG
  #undef main
#endif

namespace Skaia
{
    namespace Components
    {
        struct ENGINE_API Sprite 
        {
            Imaging::Texture* tex = nullptr;
            Imaging::Color color = {0};
            bool flipX = false;
            bool flipY = false;
            bool hasPhysics = false;
        };       
    }
}