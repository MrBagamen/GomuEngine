#include <gomu/Timer.hpp>

namespace gomu
{
Timer::Timer()
{
    //initialize
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = (double)SDL_GetTicks();
}

void Timer::stop()
{
    started = false;
    paused = false;
}

void Timer::pause()
{
    if(started == true && paused == false)
    {
        paused = true;
        pausedTicks = (double)SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if(paused)
    {
        paused = false;
        startTicks = (double)SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

double Timer::getTicks()
{
    if(started)
    {
        if(paused)
        {
            return pausedTicks;
        }
        else
        {
            return (double)SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}

bool Timer::isStarted()
{
    return started;
}
bool Timer::isPaused()
{
    return paused;
}

}
