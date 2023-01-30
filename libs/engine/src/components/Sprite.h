/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"
#include "SDL.h"
#include "behaviors/SkaiaImaging.h"

#ifdef _DEBUG
	#undef main
#endif

struct ENGINE_API S_Sprite 
{
    S_Texture* tex = nullptr;
    S_Color color = {0, 0, 0};
    bool flipX = false;
    bool flipY = false;
    bool hasPhysics = false;
};