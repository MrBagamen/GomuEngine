#ifndef GOMU_SPRITE_HPP
#define GOMU_SPRITE_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>

namespace gomu
{

class Sprite
{
public:
    void color(Uint8 _r, Uint8 _g, Uint8 _b);
    void loadImage(const char* filePath);
    void draw();
    void setPosition(int _x, int _y);
    void rotate(int angle);

    Sprite();
private:
    int x = 0, y = 0, w, h, angle;
    GLfloat quad[8];
    GLfloat texcoord[8];
    GLfloat sprite_color[12];

    GLuint texture;
};

}

#endif // GOMU_SPRITE_HPP
