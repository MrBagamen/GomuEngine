#ifndef GOMU_SOUND_HPP
#define GOMU_SOUND_HPP

#include <string>
#include <SDL.h>
#include <SDL_mixer.h>

namespace gomu
{

class Sound
{
public:
    bool loadFromFile(const std::string& filename);
    void play();

private:
    Mix_Music *music;
};

}

#endif // GOMU_SOUND_HPP
