/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "SkaiaTimer.h"

namespace Skaia
{
    namespace Timers
    {
        Timer::Timer()
        {
            // Initialize variables
            mStartTicks = 0;
            mPausedTicks = 0;;

            mPaused = false;
            mStarted = false;
        }

        void Timer::Start()
        {
            // Start the timer
            mStarted = true;

            // Unpause the timer if paused
            mPaused = false;

            // Get the current clock time
            mStartTicks = SDL_GetTicks();
            mPausedTicks = 0;
        }

        void Timer::Stop()
        {
            // Stop the timer
            mStarted = false;

            // Unpause the timer if paused
            mPaused = false;

            // Clear tick variables because we don't need them anymore
            mStartTicks = 0;
            mPausedTicks = 0;
        }

        void Timer::Pause()
        {
            // If the timer is running and isn't already paused
            if (mStarted && !mPaused)
            {
                // Pause the timer
                mPaused = true;

                // Calculate the paused ticks
                mPausedTicks = SDL_GetTicks() - mStartTicks;
                mStartTicks = 0;
            }
        }

        void Timer::Unpause()
        {
            // If the timer is both running and paused
            if (mStarted && mPaused)
            {
                // Unpause the timer
                mPaused = false;

                // Reset the starting ticks
                mStartTicks = SDL_GetTicks() - mPausedTicks;

                // Reset the paused ticks
                mPausedTicks = 0;
            }
        }

        Uint32 Timer::GetTicks()
        {
            // The actual timer time
            Uint32 time = 0;

            // Check if timer is running
            if (mStarted)
            {
                // Check if timer is currently paused
                if (mPaused)
                {
                    // If paused, return the number of ticks when the timer was paused
                    time = mPausedTicks;
                } else {
                    // Otherwise, return the current time minus the start time
                    // to get the relative time
                    time = SDL_GetTicks() - mStartTicks;
                }
            }

            return time;
        }

        bool Timer::IsStarted()
        {
            //Timer is running and paused or unpaused
            return mStarted;
        }

        bool Timer::IsPaused()
        {
            //Timer is running and paused
            return mPaused && mStarted;
        }
    }
}