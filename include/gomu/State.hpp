#ifndef GOMU_STATE_HPP
#define GOMU_STATE_HPP

#include <SDL.h>

namespace gomu
{

class State
{
public:
    virtual ~State(){}
protected:
    virtual void onUpdate(double dt) {(void)(dt);}
    virtual void onDraw() {}
    virtual void onKeyPress(SDL_Scancode key) {(void)(key);}
    friend int gomu::exec();
};

}

#endif // GOMU_STATE_HPP
