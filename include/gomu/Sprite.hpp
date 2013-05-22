#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>

namespace gomu
{

class Sprite
{
public:
    void Color(Uint8 _r, Uint8 _g, Uint8 _b);
    void LoadImage(const char* filePath);
    void Draw();
    void SetPosition(int _x, int _y);

    Sprite();
private:
    int x = 0, y = 0;
    GLfloat quad[8];
    GLfloat texcoord[8];
    GLfloat sprite_color[12];

    GLuint texture;
};

}
#endif // SPRITE_HPP
