#pragma once

#include <SDL.h>

namespace gomu
{

class State
{
public:
    virtual ~State()
    {
    }

protected:
    virtual void onUpdate(double /*dt*/)
    {
    }
    virtual void onDraw()
    {
    }
    virtual void onKeyPress(SDL_Scancode /*key*/)
    {
    }
    friend int exec();
};
}
