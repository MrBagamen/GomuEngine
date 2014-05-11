#include "gomu/Music.hpp"
#include "error.hpp"

namespace gomu
{

void Music::loadFromFile(const std::string &filename)
{
    if (!(m_music = Mix_LoadMUS(filename.c_str())))
    {
        error("Failed to load \"%s\": %s", filename.c_str(), Mix_GetError());
    }
}

void Music::play()
{
    Mix_PlayMusic(m_music, (m_looping ? -1 : 0));
}

void Music::setLooping(bool looping)
{
    m_looping = looping;
}

Music::~Music()
{
    if (m_music)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(m_music);
    }
}
}
