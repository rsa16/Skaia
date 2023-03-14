/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "AudioSystem.h"
#include <iostream>

#ifdef _DEBUG
    #undef main
#endif

namespace Skaia
{
    namespace Systems
    {
        AudioSystem::AudioSystem(Skaia::Core::Coordinator *c)
        {
            coordinator = c;

            Signature signature;
            signature.set(coordinator->GetComponentType<Components::AudioSource>());
            coordinator->SetSystemSignature<AudioSystem>(signature);
        }

        void AudioSystem::Initialize(void *data)
        {
            std::cout << "Audio System Initalized"
                    << "\n";

            for (auto const& entity : mEntities)
            {
                auto& entityAudioSource = coordinator->GetComponent<Components::AudioSource>(entity);
                if (entityAudioSource.playOnStart)
                {
                    Audio::PlayAudio(entity);
                }
            }
        }

        void AudioSystem::Render()
        {
            // nothing to implement here
        }

        void AudioSystem::Update()
        {
            for (auto const& entity : mEntities)
            {
                auto& entityAudioSource = coordinator->GetComponent<Components::AudioSource>(entity);
                if (entityAudioSource.audioClip.GetVolume() != entityAudioSource.volume)
                {
                    entityAudioSource.audioClip.SetVolume(entityAudioSource.volume);
                }
            }
        }

        void AudioSystem::Cleanup()
        {
            // nothing to implement here
        }

        void AudioSystem::HandleEvent(Events::Event* event)
        {
            Events::AudioEvent* ev = dynamic_cast<Events::AudioEvent*>(event);
            auto& entityAudioSource = coordinator->GetComponent<Components::AudioSource>(ev->entity);
            entityAudioSource.volume = ev->volume;

            switch (ev->type)
            {
                case Events::AudioEventType::START_AUDIO:
                    entityAudioSource.audioClip.Play(1);
                    break;
                
                case Events::AudioEventType::PAUSE_AUDIO:
                    entityAudioSource.audioClip.Pause();
                    break;
                
                case Events::AudioEventType::STOP_AUDIO:
                    entityAudioSource.audioClip.Stop();
                    break;
                
                case Events::AudioEventType::CHANGE_VOLUME:
                    // we already changed the volume so nothing to do here
                    break;
            }
        }
    }
}