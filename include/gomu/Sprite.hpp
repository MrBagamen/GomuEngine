#pragma once

#include <gomu/Texture.hpp>

#include <SDL.h>

namespace gomu
{

class Sprite
{
public:
    void color(Uint8 _r, Uint8 _g, Uint8 _b);
    void setTexture(const Texture& texture);
    void draw();
    void setPosition(int _x, int _y);
    void rotate(int angle);

    Sprite();
private:
    int x = 0, y = 0, angle;
    GLfloat quad[8];
    GLfloat texcoord[8];
    GLfloat sprite_color[12];
    const Texture* m_texture;
};

}
