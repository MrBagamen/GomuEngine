#pragma once

#include <SDL_mixer.h>
#include <string>

namespace gomu
{

class Music {
public:
    bool loadFromFile(const std::string& filename);
    void play();
    void setLooping(bool looping);
    ~Music();
private:
    Mix_Music* m_music = nullptr;
    bool m_looping = false;
};

}
