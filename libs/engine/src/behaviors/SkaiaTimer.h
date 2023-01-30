#include <SDL.h>

class S_Timer 
{
    private:
        Uint32 mStartTicks;
        Uint32 mPausedTicks;

        bool mPaused;
        bool mStarted;

    public:
        S_Timer();

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