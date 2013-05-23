#ifndef GOMU_FONT_HPP
#define GOMU_FONT_HPP

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

#endif // GOMU_FONT_HPP
