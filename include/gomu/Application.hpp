#ifndef GOMU_APPLICATION_HPP
#define GOMU_APPLICATION_HPP

#include <string>
#include <map>
#include <gomu/State.hpp>

namespace gomu
{

class Application
{
public:
    Application(int width, int height, const std::string& title = std::string());
    void addState(State* state, const std::string& name);
    void setState(const std::string& name);
    int exec();
private:
    int m_width;
    int m_height;
    const std::string& m_title;
    std::map<std::string, State*> m_states;
    State* m_state;
};

}

#endif // GOMU_APPLICATION_HPP
