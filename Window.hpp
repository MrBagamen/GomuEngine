#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <GL/gl.h>

class Window
{
public:
    Window();

    void create(int _w, int _h, const char* _title);
    bool isRunning();
    void update();
private:
    unsigned int WIDTH, HEIGHT;
    SDL_Event event;
};

#endif // WINDOW_HPP
