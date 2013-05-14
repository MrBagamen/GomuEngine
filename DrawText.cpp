#include "DrawText.hpp"

DrawText::DrawText()
{
	text_color = {0, 0, 0};
	x = y = 0;
}

void DrawText::Init()
{
	if(TTF_Init() != 0)
	{
		printf("Error: %s\n", TTF_GetError());
		exit(1);
	}
	printf("Initialized SDL_ttf\n");

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DrawText::loadFont(const char* file, int ptsize)
{
	TTF_Font* temp;
	temp = TTF_OpenFont(file, ptsize);
	if(temp == nullptr)
	{
		printf("Error %s\n", TTF_GetError());
	}
	printf("Loaded %s\n", file);
	font = temp;
}

void DrawText::textColor(Uint8 _r, Uint8 _g, Uint8 _b)
{
	text_color = {_r, _g, _b};
}

void DrawText::setText(const char* text)
{
	img = TTF_RenderText_Blended(font, text, text_color);

	glDeleteTextures(1, &texture);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, img->pixels);
}

void DrawText::Draw()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glTexCoord2i(0, 0); glVertex2i(x, y);
		glTexCoord2i(1, 0); glVertex2i(x+img->w, y);
		glTexCoord2i(1, 1); glVertex2i(x+img->w, y+img->h);
		glTexCoord2i(0, 1); glVertex2i(x, y+img->h);
	glEnd();
	glPopMatrix();
}

void DrawText::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}