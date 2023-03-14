/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "Types.h"
#include "SkaiaEvents.h"
#include <SDL_mixer.h>
#include <memory>

#ifdef _DEBUG
    #undef main
#endif

namespace Skaia
{
    namespace Audio
    {

        class ENGINE_API AudioClip
        {
            private:
                Mix_Chunk* sound;
                Mix_Music* music;
                bool isMusic;

                int volume = 128;
                int channel = -1;

            public:
                AudioClip();
                void LoadSound(std::string file);
                void LoadMusic(std::string file);

                void Play(int loops);
                void Pause();
                void Stop();

                void SetVolume(int volume); // SetVolume will only work specific to the AudioClip if it is a sound. Using it on music will change universally. 
                int GetVolume() { return volume; }
        };

        void PlayAudio(Skaia::Entity entity);
        void StopAudio(Skaia::Entity entity);
        void ChangeVolume(Skaia::Entity entity, int volume);
    }
}