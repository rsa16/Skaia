/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "InputSystem.h"
#include <iostream>

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace Systems
    {
        InputSystem::InputSystem(Skaia::Core::Coordinator* c)
        {
            coordinator = c;

            Signature signature;
            signature.set(coordinator->GetComponentType<Components::Input>());
            coordinator->SetSystemSignature<Systems::InputSystem>(signature);
        }

        void InputSystem::Initialize(void* data)
        {
            std::cout << "Input System Initialized" << "\n";
        }

        void InputSystem::Update()
        {
            // nothing to do here
        }

        void InputSystem::Render()
        {
            // nothing to do here
        }

        void InputSystem::Cleanup()
        {
            // nothing to do here
        }

        bool InputSystem::HandleEvent(Events::Event* event)
        {
            Events::KeyboardEvent* ev = dynamic_cast<Events::KeyboardEvent*>(event);
            for (auto const& entity : mEntities)
            {
                auto& entityInputComponent = coordinator->GetComponent<Components::Input>(entity);

                if (ev->type == Events::KeyboardEventType::KEYDOWN)
                {
                    entityInputComponent.UP_PRESSED = (ev->sym == entityInputComponent.UP ? true : entityInputComponent.UP_PRESSED);
                    entityInputComponent.DOWN_PRESSED = (ev->sym == entityInputComponent.DOWN ? true : entityInputComponent.DOWN_PRESSED);
                    entityInputComponent.LEFT_PRESSED = (ev->sym == entityInputComponent.LEFT ? true : entityInputComponent.LEFT_PRESSED);
                    entityInputComponent.RIGHT_PRESSED = (ev->sym == entityInputComponent.RIGHT ? true : entityInputComponent.RIGHT_PRESSED);

                } else if (ev->type == Events::KeyboardEventType::KEYUP)
                {
                    entityInputComponent.UP_PRESSED = (ev->sym == entityInputComponent.UP ? false : entityInputComponent.UP_PRESSED);
                    entityInputComponent.DOWN_PRESSED = (ev->sym == entityInputComponent.DOWN ? false : entityInputComponent.DOWN_PRESSED);
                    entityInputComponent.LEFT_PRESSED = (ev->sym == entityInputComponent.LEFT ? false : entityInputComponent.LEFT_PRESSED);
                    entityInputComponent.RIGHT_PRESSED = (ev->sym == entityInputComponent.RIGHT ? false : entityInputComponent.RIGHT_PRESSED);
                }
            }
            return true;
        }
    }
}