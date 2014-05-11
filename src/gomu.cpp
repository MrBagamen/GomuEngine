#include <gomu/gomu.hpp>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <GL/glew.h>
#include <gomu/Timer.hpp>
#include "error.hpp"

namespace gomu
{

int m_width;
int m_height;
std::string m_title;
std::map<std::string, State *> m_states;
State *m_state;
const Uint8 *m_keyState;
bool m_fullscreen;
SDL_Window *m_window;
SDL_GLContext m_glcontext;
bool m_running;

void init(int width, int height, bool fullscreen, const std::string &title)
{
    m_width = width;
    m_height = height;
    m_title = title;
    m_state = nullptr;
    m_fullscreen = fullscreen;
    m_window = nullptr;
    m_glcontext = nullptr;

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        error("Error initializing SDL: %s\n", SDL_GetError());
    }
    if (!IMG_Init(IMG_INIT_PNG))
    {
        error("Error initializing SDL_image: %s\n", IMG_GetError());
    }

    int videoflags = SDL_WINDOW_OPENGL;

    if (m_fullscreen)
    {
        videoflags |= SDL_WINDOW_FULLSCREEN;
    }

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                                videoflags);
    m_glcontext = SDL_GL_CreateContext(m_window);

    if (!m_window)
    {
        error("Error setting video mode: %s\n", SDL_GetError());
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_width, m_height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        error("Error: %s\n", glewGetErrorString(err));
    }

    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);

    if (TTF_Init())
    {
        error("Error initializing SDL_ttf: %s\n", TTF_GetError());
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_keyState = SDL_GetKeyboardState(nullptr);
}

void cleanUp()
{
    for (auto &pair : m_states)
    {
        delete pair.second;
    }

    SDL_GL_DeleteContext(m_glcontext);
    SDL_DestroyWindow(m_window);
    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

void addState(State *state, const std::string &name)
{
    m_states[name] = state;
}

void setState(const std::string &name)
{
    m_state = m_states[name];
}

int exec()
{
    if (!m_state)
    {
        puts("Error: No state set. Exiting.");
        return 1;
    }

    m_running = true;

    Timer deltaTime;
    deltaTime.start();

    while (m_running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                m_state->onKeyPress(event.key.keysym.scancode);
            }
        }

        m_state->onUpdate(deltaTime.getTicks() / 1000.0f);
        deltaTime.start(); // restart timer

        glClear(GL_COLOR_BUFFER_BIT);
        m_state->onDraw();
        SDL_GL_SwapWindow(m_window);
    }

    cleanUp();
    return 0;
}

bool toggleFullscreen()
{
    m_fullscreen = !m_fullscreen;

    SDL_SetWindowFullscreen(m_window,
                            (m_fullscreen ? SDL_WINDOW_FULLSCREEN : 0));

    return m_fullscreen;
}

void quit()
{
    m_running = false;
}

void setBackgroundColor(int r, int g, int b)
{
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}
}
