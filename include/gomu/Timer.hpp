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
    double startTicks;
    double pausedTicks;

    bool paused;
    bool started;
};
}
