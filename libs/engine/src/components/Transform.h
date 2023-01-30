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

struct ENGINE_API S_Transform 
{
    float x, y;
    int width, height;

    float rotation = 0;
};