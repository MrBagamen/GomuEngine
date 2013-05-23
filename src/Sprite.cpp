#include "gomu/Sprite.hpp"

namespace gomu
{

Sprite::Sprite() :
    texcoord
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    },
    sprite_color
    {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    }
{
    x = 0;
    y = 0;
}

void Sprite::draw()
{
    glPushMatrix();
    m_texture->bind();
    glTranslatef(x+m_texture->getWidth()/2, y+m_texture->getHeight()/2, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glColorPointer(3, GL_FLOAT, 0, sprite_color);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
    glDrawArrays(GL_QUADS, 0, 8);
    glPopMatrix();
}

void Sprite::rotate(int _angle)
{
    angle = _angle;
}

void Sprite::color(Uint8 _r, Uint8 _g, Uint8 _b)
{
    sprite_color[0] = sprite_color[3] = sprite_color[6] = sprite_color[9] = _r / 255.0f;
    sprite_color[1] = sprite_color[4] = sprite_color[7] = sprite_color[10] = _g / 255.0f;
    sprite_color[2] = sprite_color[5] = sprite_color[8] = sprite_color[11] = _b / 255.0f;
}

void Sprite::setTexture(const Texture &texture)
{
    m_texture = &texture;
    quad[0] =-m_texture->getWidth()/2;  quad[1] =-m_texture->getWidth()/2;
    quad[2] = m_texture->getWidth()/2;  quad[3] =-m_texture->getWidth()/2;
    quad[4] = m_texture->getWidth()/2;  quad[5] = m_texture->getWidth()/2;
    quad[6] =-m_texture->getWidth()/2;  quad[7] = m_texture->getWidth()/2;
}

void Sprite::setPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}

}
