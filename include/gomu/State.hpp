#ifndef GOMU_STATE_HPP
#define GOMU_STATE_HPP

#include <SDL.h>

namespace gomu
{

class State
{
protected:
    virtual void onUpdate(double dt) {}
    virtual void onDraw() {}
    virtual void onKeyPress(SDLKey key) {}
    friend class Application;
};

}

#endif // GOMU_STATE_HPP
