#include <gomu/Font.hpp>

#include "error.hpp"

namespace gomu
{

Font::Font() : handle(nullptr)
{
}

Font::~Font()
{
    TTF_CloseFont(handle);
}

void Font::openFromFile(const std::string &filename, int ptsize)
{
    handle = TTF_OpenFont(filename.c_str(), ptsize);
    if (!handle)
    {
        error("Failed to open \"%s\". Reason: %s", filename.c_str(),
              TTF_GetError());
    }
}
}
