#include <gomu/Application.hpp>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <GL/glew.h>

namespace gomu
{

// Internally used pointer to the instance of gomu::Application
Application* _application;

Application::Application(int width, int height, bool fullscreen = false, const std::string &title) :
    m_width(width),
    m_height(height),
    m_title(title),
    m_state(nullptr),
    m_fullscreen(fullscreen),
    m_window(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        throw;
    }
    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("Error initializing SDL_image: %s\n", IMG_GetError());
        throw;
    }

    int videoflags = SDL_WINDOW_OPENGL;

    if (m_fullscreen)
    {
        videoflags |= SDL_WINDOW_FULLSCREEN;
    }

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, videoflags);

    if (!m_window)
    {
        printf("Error setting video mode: %s\n", SDL_GetError());
        throw;
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
        printf("Error: %s\n", glewGetErrorString(err));
        throw;
    }

    if(TTF_Init())
    {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        throw;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_keyState = SDL_GetKeyboardState(nullptr);
    _application = this;
}

Application::~Application()
{
    for (auto& pair : m_states)
    {
        delete pair.second;
    }

    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

void Application::addState(State *state, const std::string &name)
{
    m_states[name] = state;
}

void Application::setState(const std::string &name)
{
    m_state = m_states[name];
}

int Application::exec()
{
    if (!m_state)
    {
        puts("Error: No state set. Exiting.");
        return 1;
    }

    for (;;)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                m_state->onKeyPress(event.key.keysym.sym);
            }
        }

        m_state->onUpdate(1);
        m_state->onDraw();
        SDL_GL_SwapWindow(m_window);
    }
}

bool toggleFullscreen()
{
    _application->m_fullscreen = !(_application->m_fullscreen);

    SDL_SetWindowFullscreen(_application->m_window, (_application->m_fullscreen ? SDL_WINDOW_FULLSCREEN : 0));

    return _application->m_fullscreen;
}

}
