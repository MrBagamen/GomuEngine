#ifndef STATE_HPP
#define STATE_HPP

namespace gomu
{

class State
{
protected:
    virtual void onUpdate(double dt) {}
    virtual void onDraw() {}
    friend class Application;
};

}

#endif // STATE_HPP
