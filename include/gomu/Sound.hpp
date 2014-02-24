#pragma once

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
