#include <gomu/input.hpp>

namespace gomu
{

bool isKeyDown(SDL_Scancode key)
{
    extern const Uint8 *m_keyState;
    return m_keyState[key];
}
}
