#pragma once

#include <string>

#include <GL/glew.h>

namespace gomu
{

class Texture
{
public:
    void loadFromFile(const std::string& filename);
    int getWidth() const;
    int getHeight() const;
    void bind() const;
    ~Texture();
private:
    GLuint m_handle;
    int m_width, m_height;
};

}
