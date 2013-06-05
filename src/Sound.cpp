#include <gomu/Sound.hpp>

namespace gomu
{

bool Sound::loadFromFile(const std::string& filename)
{
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
    if(!(music = Mix_LoadMUS(filename.c_str())))
    {
        printf("Unable to load %s\n", filename.c_str());
        return false;
    }
    return true;
}

void Sound::play()
{
    Mix_PlayMusic(music, 0);
}

}
