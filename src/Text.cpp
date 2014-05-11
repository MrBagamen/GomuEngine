#include <gomu/Text.hpp>

namespace gomu
{

Text::Text()
    : m_x(0), m_y(0),
      m_texcoord{ 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f },
      m_texture(0), m_surface(nullptr),
      m_colors{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },
      m_font(nullptr)
{
}

Text::~Text()
{
    glDeleteTextures(1, &m_texture);
}

void Text::update()
{
    if (m_string.empty() || !m_font)
    {
        return;
    }
    m_surface = TTF_RenderText_Blended(m_font->m_handle, m_string.c_str(),
                                       { 255, 255, 255, 0 });
    glDeleteTextures(1, &m_texture);
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
    m_quad[0] = 0.0f;
    m_quad[1] = 0.0f;
    m_quad[2] = m_surface->w;
    m_quad[3] = 0.0f;
    m_quad[4] = m_surface->w;
    m_quad[5] = m_surface->h;
    m_quad[6] = 0.0f;
    m_quad[7] = m_surface->h;
    SDL_FreeSurface(m_surface);
}

void Text::setFont(const Font &font)
{
    m_font = &font;
}

void Text::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    m_colors[0] = m_colors[3] = m_colors[6] = m_colors[9] = r / 255.0f;
    m_colors[1] = m_colors[4] = m_colors[7] = m_colors[10] = g / 255.0f;
    m_colors[2] = m_colors[5] = m_colors[8] = m_colors[11] = b / 255.0f;
    update();
}

void Text::setString(const std::string &str)
{
    m_string = str;
    update();
}

void Text::draw()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTranslatef(m_x, m_y, 0.0f);
    glVertexPointer(2, GL_FLOAT, 0, m_quad);
    glColorPointer(3, GL_FLOAT, 0, m_colors);
    glTexCoordPointer(2, GL_FLOAT, 0, m_texcoord);
    glDrawArrays(GL_QUADS, 0, 4);
    glPopMatrix();
}

void Text::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}
}
