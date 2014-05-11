#pragma once

#include <gomu/Font.hpp>

#include <SDL.h>
#include <GL/glew.h>

#include <string>

namespace gomu
{

class Text
{
public:
    Text();
    ~Text();
    void setFont(const Font &font);
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void setString(const std::string &str);
    void setPosition(int x, int y);
    void draw();

private:
    void update();
    int m_x, m_y;

    GLfloat m_quad[8];
    GLfloat m_texcoord[8];

    GLuint m_texture;
    SDL_Surface *m_surface;
    GLfloat m_colors[12];
    const Font *m_font;
    std::string m_string;
};
}
