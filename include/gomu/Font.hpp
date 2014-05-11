#pragma once

#include <SDL_ttf.h>
#include <string>

namespace gomu
{

struct Font
{
public:
    Font();
    ~Font();
    void openFromFile(const std::string &filename, int ptsize);
    TTF_Font *m_handle;
};
}
