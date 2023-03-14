/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "SkaiaCore.h"
#include "Types.h"
#include "behaviors/SkaiaAudio.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Components
    {
        struct ENGINE_API AudioSource
        {
            Audio::AudioClip audioClip;
            int volume = 128;
            bool playOnStart = false;
        };
    }
}