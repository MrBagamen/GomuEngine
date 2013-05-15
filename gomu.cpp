#include "gomu.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>

namespace gomu
{

int windowWidth, windowHeight;

bool init(int width, int height, const std::string &title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    windowWidth = width;
    windowHeight = height;

    if (!SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_HWSURFACE | SDL_OPENGL))
    {
        printf("Error setting video mode: %s\n", SDL_GetError());
        return false;
    }

    SDL_WM_SetCaption(title.c_str(), nullptr);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        printf("Error: %s\n", glewGetErrorString(err));
        return false;
    }

    if(TTF_Init())
    {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        return false;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

int getWindowWidth()
{
    return windowWidth;
}

int getWindowHeight()
{
    return windowHeight;
}

}
