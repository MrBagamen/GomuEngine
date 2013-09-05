#ifndef GOMU_DRAWTEXT_HPP
#define GOMU_DRAWTEXT_HPP

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
    void setFont(const Font& font);
	void textColor(Uint8 _r, Uint8 _g, Uint8 _b);
    void setString(const std::string &m_string);
	void setPosition(int _x, int _y);
    void draw();
private:
    void update();
	int x, y;

    GLfloat quad[8];
    GLfloat texcoord[8];

	GLuint texture;
	SDL_Surface* img;
    GLfloat text_color[12];
    SDL_Color default_color;
    const Font* m_font;
    std::string m_string;
};

}

#endif // GOMU_DRAWTEXT_HPP
