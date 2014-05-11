#include <gomu/Timer.hpp>

namespace gomu
{
Timer::Timer()
{
    // initialize
    m_startTicks = 0;
    m_pausedTicks = 0;
    m_paused = false;
    m_started = false;

    start();
}

void Timer::start()
{
    m_started = true;
    m_paused = false;
    m_startTicks = (double)SDL_GetTicks();
}

void Timer::stop()
{
    m_started = false;
    m_paused = false;
}

void Timer::pause()
{
    if (m_started == true && m_paused == false)
    {
        m_paused = true;
        m_pausedTicks = (double)SDL_GetTicks() - m_startTicks;
    }
}

void Timer::unpause()
{
    if (m_paused)
    {
        m_paused = false;
        m_startTicks = (double)SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
    }
}

double Timer::getTicks()
{
    if (m_started)
    {
        if (m_paused)
        {
            return m_pausedTicks;
        }
        else
        {
            return (double)SDL_GetTicks() - m_startTicks;
        }
    }
    return 0;
}

bool Timer::isStarted()
{
    return m_started;
}
bool Timer::isPaused()
{
    return m_paused;
}
}
