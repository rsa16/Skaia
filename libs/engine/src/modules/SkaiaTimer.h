/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include <SDL.h>
#include "Types.h"

namespace Skaia
{
    class ENGINE_API Timer 
    {
        private:
            Uint32 mStartTicks;
            Uint32 mPausedTicks;

            bool mPaused;
            bool mStarted;

        public:
            Timer();

            // Various clock actions
            void Start();
            void Stop();
            void Pause();
            void Unpause();

            // Get timer's time (lol?)
            Uint32 GetTicks();

            // These functions check the status of the timer
            bool IsStarted();
            bool IsPaused();
    };
}