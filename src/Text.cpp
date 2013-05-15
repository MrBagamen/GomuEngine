#include <gomu/Text.hpp>

namespace gomu
{

Text::Text() :
    x(0),y(0),
    texcoord{
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    },
    texture(0),
    img(nullptr),
    text_color {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    },
    font(nullptr)
{
}

void Text::update()
{
    if (string.empty() || !font)
    {
        return;
    }
    default_color = {255, 255, 255, 0};
    img = TTF_RenderText_Blended(font, string.c_str(), default_color);
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
    text_color[0] = text_color[3] = text_color[6] = text_color[9] = _r / 255.0f;
    text_color[1] = text_color[4] = text_color[7] = text_color[10] = _g / 255.0f;
    text_color[2] = text_color[5] = text_color[8] = text_color[11] = _b / 255.0f;
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

    quad[0] = 0.0f;  quad[1] = 0.0f;
    quad[2] = img->w;quad[3] = 0.0f;
    quad[4] = img->w;quad[5] = img->h;
    quad[6] = 0.0f;  quad[7] = img->h;

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(x, y, 0.0f);
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glColorPointer(3, GL_FLOAT, 0, text_color);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
    glDrawArrays(GL_QUADS, 0, 8);
    glPopMatrix();
}

void Text::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

}
