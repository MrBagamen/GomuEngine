#include <gomu/input.hpp>

#include <gomu/Application.hpp>

namespace gomu
{

extern Application* _application;

bool isKeyDown(SDLKey key)
{
    return _application->m_keyState[key];
}

}