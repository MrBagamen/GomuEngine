#include <gomu/Texture.hpp>

#include <SDL_image.h>

namespace gomu
{

bool Texture::loadFromFile(const std::string& filename)
{
    SDL_Surface *img = IMG_Load(filename.c_str());

    if(!img)
    {
        printf("Error: %s\n", IMG_GetError());
        return false;
    }

    m_width = img->w;
    m_height = img->h;

    //Build Texture
    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // TODO: We assume that the pixel data is always in RGBA format.
    // It might not always be the case.
    // We could examine the SDL_Surface for the format of the pixel data.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
    SDL_FreeSurface(img);
    return true;
}

int Texture::getWidth() const
{
    return m_width;
}

int Texture::getHeight() const
{
    return m_height;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
}

}
