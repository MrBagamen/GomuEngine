#include <gomu/Sound.hpp>
#include "error.hpp"

namespace gomu
{

void Sound::loadFromFile(const std::string &filename)
{
    if (!(m_chunk = Mix_LoadWAV(filename.c_str())))
    {
        error("Unable to load %s\n", filename.c_str());
    }
}

void Sound::play()
{
    Mix_PlayChannel(-1, m_chunk, false);
}

Sound::~Sound()
{
    if (m_chunk)
        Mix_FreeChunk(m_chunk);
}
}
