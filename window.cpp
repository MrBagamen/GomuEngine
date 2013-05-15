#include "window.hpp"

Window::Window()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        exit(1);
    }
}

void Window::create(int _w, int _h, const char* _title)
{
    SDL_SetVideoMode(_w, _h, 32, SDL_HWSURFACE | SDL_OPENGL);
    SDL_WM_SetCaption(_title, nullptr);

    WIDTH = _w;
    HEIGHT = _h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
}

bool Window::isRunning()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            return false;
        break;
        default:;
        }
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    return true;
}

void Window::update()
{
    SDL_GL_SwapBuffers();
}
