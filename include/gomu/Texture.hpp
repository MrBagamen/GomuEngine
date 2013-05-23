#ifndef GOMU_TEXTURE_HPP
#define GOMU_TEXTURE_HPP

#include <string>

#include <GL/glew.h>

namespace gomu
{

class Texture
{
public:
    bool loadFromFile(const std::string& filename);
    int getWidth() const;
    int getHeight() const;
    void bind() const;
    ~Texture();
private:
    GLuint m_handle;
    int m_width, m_height;
};

}

#endif // GOMU_TEXTURE_HPP
