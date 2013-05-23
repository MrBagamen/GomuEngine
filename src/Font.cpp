#include <gomu/Font.hpp>

namespace gomu
{

Font::Font() :
    handle(nullptr)
{
}

Font::~Font()
{
    TTF_CloseFont(handle);
}

bool Font::openFromFile(const std::string &filename, int ptsize)
{
    handle = TTF_OpenFont(filename.c_str(), ptsize);
    return handle;
}



}
