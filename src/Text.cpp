#include <gomu/Text.hpp>

namespace gomu
{

Text::Text() :
    x(0),y(0),
    texture(0),
    img(nullptr),
    text_color({0,0,0,0}),
    font(nullptr)
{
}

void Text::update()
{
    if (string.empty() || !font)
    {
        return;
    }

    img = TTF_RenderText_Blended(font, string.c_str(), text_color);
    glDeleteTextures(1, &texture);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, img->pixels);
}

void Text::loadFont(const char* file, int ptsize)
{
	TTF_Font* temp;
	temp = TTF_OpenFont(file, ptsize);
	if(temp == nullptr)
	{
		printf("Error %s\n", TTF_GetError());
	}
	printf("Loaded %s\n", file);
	font = temp;
    update();
}

void Text::textColor(Uint8 _r, Uint8 _g, Uint8 _b)
{
    text_color = {_r, _g, _b, 0};
    update();
}

void Text::setString(const std::string& string)
{
    this->string = string;
    update();
}

void Text::draw()
{
    if (!img)
    {
        return;
    }

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

void Text::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

}
