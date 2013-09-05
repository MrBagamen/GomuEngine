#ifndef GOMU_APPLICATION_HPP
#define GOMU_APPLICATION_HPP

#include <string>
#include <map>
#include <gomu/State.hpp>

#include <SDL.h>

namespace gomu
{

class Application
{
public:
    Application(int width, int height, bool fullscreen, const std::string& title = std::string());
    ~Application();
    void addState(State* state, const std::string& name);
    void setState(const std::string& name);
    int exec();
private:
    int m_width;
    int m_height;
    const std::string& m_title;
    std::map<std::string, State*> m_states;
    State* m_state;
    const Uint8* m_keyState;
    bool m_fullscreen;
    SDL_Window* m_window;
    SDL_GLContext m_glcontext;
    friend bool isKeyDown(SDL_Scancode);
    friend bool toggleFullscreen();
};

bool toggleFullscreen();

}

#endif // GOMU_APPLICATION_HPP
