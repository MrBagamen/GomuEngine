#include <gomu/Application.hpp>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL/glew.h>

namespace gomu
{

// Internally used pointer to the instance of gomu::Application
Application* _application;

Application::Application(int width, int height, const std::string &title) :
    m_width(width),
    m_height(height),
    m_title(title),
    m_state(nullptr)
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

    if (!SDL_SetVideoMode(m_width, m_height, 32, SDL_HWSURFACE | SDL_OPENGL))
    {
        printf("Error setting video mode: %s\n", SDL_GetError());
        throw;
    }

    SDL_WM_SetCaption(m_title.c_str(), nullptr);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_width, m_height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

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

    m_keyState = SDL_GetKeyState(nullptr);
    _application = this;
}

Application::~Application()
{
    TTF_Quit();
    IMG_Quit();
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
        }

        m_state->onUpdate(1);
        glClear(GL_COLOR_BUFFER_BIT);
        m_state->onDraw();
        SDL_GL_SwapBuffers();
    }
}

}
