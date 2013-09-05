#ifndef GOMU_APPLICATION_HPP
#define GOMU_APPLICATION_HPP

#include <string>
#include <map>
#include <gomu/State.hpp>

namespace gomu
{

void init(int width, int height, bool fullscreen, const std::string& title = std::string());
void quit();

void addState(State* state, const std::string& name);
void setState(const std::string& name);

int exec();

bool toggleFullscreen();

}

#endif // GOMU_APPLICATION_HPP