#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/gl.h>

class Window
{
public:
    Window();

    void Create(int _w, int _h, const char* _title);
    bool isRunning();
    void Update();
private:
    unsigned int WIDTH, HEIGHT;
    SDL_Event event;
};

#endif // WINDOW_HPP
