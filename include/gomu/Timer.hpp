#pragma once

#include <SDL_timer.h>

namespace gomu
{
class Timer
{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    double getTicks();

    bool isStarted();
    bool isPaused();

private:
    double m_startTicks;
    double m_pausedTicks;

    bool m_paused;
    bool m_started;
};
}
