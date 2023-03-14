/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "SkaiaEvents.h"

namespace Skaia
{
    namespace Events
    {
        std::queue<Event*> CENTRAL_EVENT_QUEUE;

        void ENGINE_API DispatchEvent(Event* ev)
        {
            CENTRAL_EVENT_QUEUE.push(ev);
        }

        int CheckEvent(Event** ev)
        {
            SDL_Event sdlEvent;
            if (SDL_PollEvent(&sdlEvent) != 0)
            {
                switch (sdlEvent.type)
                {
                    case SDL_KEYDOWN: case SDL_KEYUP:
                        {
                            KeyboardEvent kEvent;
                            kEvent.name = EventNames::KEYBOARD_EVENT;
                            kEvent.state = sdlEvent.key.state;
                            kEvent.repeat = sdlEvent.key.repeat;
                            kEvent.timestamp = sdlEvent.key.timestamp;
                            kEvent.sym = sdlEvent.key.keysym.sym;
                            kEvent.type = (sdlEvent.type == SDL_KEYDOWN) ? KeyboardEventType::KEYDOWN : KeyboardEventType::KEYUP;

                            DispatchEvent(new KeyboardEvent(kEvent));
                        }
                        break;

                    case SDL_QUIT:
                        {
                            QuitEvent qEvent;
                            qEvent.type = sdlEvent.type;
                            qEvent.name = EventNames::QUIT_EVENT;

                            DispatchEvent(new QuitEvent(qEvent));
                        }
                        break;
                }
            }

            if (!CENTRAL_EVENT_QUEUE.empty())
            {
                *ev = CENTRAL_EVENT_QUEUE.front();
                CENTRAL_EVENT_QUEUE.pop();
                return 0;
            } else {
                return -1;
            }
        }
    }
}