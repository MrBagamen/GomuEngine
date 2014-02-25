#include <gomu/Sound.hpp>

namespace gomu
{

bool Sound::loadFromFile(const std::string& filename)
{
    if(!(m_chunk = Mix_LoadWAV(filename.c_str())))
    {
        printf("Unable to load %s\n", filename.c_str());
        return false;
    }
    return true;
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
