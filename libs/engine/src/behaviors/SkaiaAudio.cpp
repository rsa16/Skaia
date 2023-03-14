/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "SkaiaAudio.h"
#include "SkaiaEvents.h"

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Audio
    {
        AudioClip::AudioClip()
        {
            // do nothing
        }

        void AudioClip::LoadSound(std::string file)
        {
            sound = Mix_LoadWAV(file.c_str());
        }

        void AudioClip::LoadMusic(std::string file)
        {
            music = Mix_LoadMUS(file.c_str());
        }

        void AudioClip::Play(int loops)
        {
            if (isMusic)
            {
                if( Mix_PlayingMusic() == 0 )
                {
                    Mix_PlayMusic( music, (loops - 1) );
                }
            } else {
                channel = Mix_PlayChannel( -1, sound, (loops - 1) );
            }
        }

        void AudioClip::Pause()
        {
            if (isMusic)
            {
                Mix_PauseMusic();
            } else {
                if (channel >= 0)
                {
                    Mix_Pause(channel);
                }
            }
        }

        // sounds are assumed to be short so no api to stop them in sdl
        void AudioClip::Stop()
        {
            if (isMusic)
            {
                Mix_HaltMusic();
            }
        }

        void AudioClip::SetVolume(int vol)
        {
            volume = vol;
            if (isMusic)
            {
                Mix_VolumeMusic(vol);
            } else {
                Mix_VolumeChunk(sound, vol);
            }
        }

        void PlayAudio(Skaia::Entity entity)
        {
            Events::AudioEvent* playEvent = new Events::AudioEvent();
            playEvent->entity = entity;
            playEvent->type = Events::AudioEventType::START_AUDIO;

            Events::DispatchEvent(playEvent);
        }

        void StopAudio(Skaia::Entity entity)
        {
            Events::AudioEvent* stopEvent = new Events::AudioEvent();
            stopEvent->entity = entity;
            stopEvent->type = Events::AudioEventType::STOP_AUDIO;

            Events::DispatchEvent(stopEvent);
        }

        void ChangeVolume(Skaia::Entity entity, int volume)
        {
            Events::AudioEvent* volumeEvent = new Events::AudioEvent();
            volumeEvent->entity = entity;
            volumeEvent->type = Events::AudioEventType::CHANGE_VOLUME;
            volumeEvent->volume = volume;

            Events::DispatchEvent(volumeEvent);
        }
    }
}