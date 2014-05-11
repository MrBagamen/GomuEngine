#include <gomu/Font.hpp>

#include "error.hpp"

namespace gomu
{

Font::Font() : m_handle(nullptr)
{
}

Font::~Font()
{
    TTF_CloseFont(m_handle);
}

void Font::openFromFile(const std::string &filename, int ptsize)
{
    m_handle = TTF_OpenFont(filename.c_str(), ptsize);
    if (!m_handle)
    {
        error("Failed to open \"%s\". Reason: %s", filename.c_str(),
              TTF_GetError());
    }
}
}
