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

void Sprite::loadImage(const char *filePath)
{
    SDL_Surface *img = IMG_Load(filePath);
    if(!img)
    {
        printf("Error: %s\n", IMG_GetError());
        exit(1);
    }
    printf("Loaded %s\n", filePath);
    w = img->w;
    h = img->h;

    //Build Texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, img->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    quad[0] =-w/2;  quad[1] =-w/2;
    quad[2] = w/2;  quad[3] =-w/2;
    quad[4] = w/2;  quad[5] = w/2;
    quad[6] =-w/2;  quad[7] = w/2;

    SDL_FreeSurface(img);
}

void Sprite::draw()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(x+w/2, y+h/2, 0.0f);
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

void Sprite::setPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}

}