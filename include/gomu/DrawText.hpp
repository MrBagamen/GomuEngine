#ifndef DRAWTEXT_HPP_INCLUDED
#define DRAWTEXT_HPP_INCLUDED

#include <SDL_ttf.h>
#include <SDL.h>
#include <GL/gl.h>

#include <string>

class DrawText
{
public:
	DrawText();
	void loadFont(const char* file, int ptsize);
	void textColor(Uint8 _r, Uint8 _g, Uint8 _b);
    void setString(const std::string &string);
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
	TTF_Font* font;
    std::string string;
};

#endif
