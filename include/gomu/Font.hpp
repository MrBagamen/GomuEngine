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
    bool openFromFile(const std::string& filename, int ptsize);
    TTF_Font* handle;
};

}
