#ifndef DRAWTEXT_HPP_INCLUDED
#define DRAWTEXT_HPP_INCLUDED

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <GL/gl.h>

class DrawText
{
public:
	DrawText();
	void loadFont(const char* file, int ptsize);
	void textColor(Uint8 _r, Uint8 _g, Uint8 _b);
	void setText(const char* text);
	void setPosition(int _x, int _y);
	void Draw();

	static void Init();
private:
	int x, y;

	GLuint texture;
	SDL_Surface* img;
	SDL_Color text_color;
	TTF_Font* font;
};

#endif
