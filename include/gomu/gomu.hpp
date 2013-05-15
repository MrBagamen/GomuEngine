#ifndef GOMU_HPP_INCLUDED
#define GOMU_HPP_INCLUDED

#include <string>

namespace gomu
{

bool init(int width, int height, const std::string& title = std::string());
int getWindowWidth();
int getWindowHeight();

}

#endif
