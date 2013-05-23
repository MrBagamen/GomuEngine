#ifndef GOMU_STATE_HPP
#define GOMU_STATE_HPP

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

#endif // GOMU_STATE_HPP
