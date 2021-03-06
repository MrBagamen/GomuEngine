#pragma once

#include <GL/glew.h>
#include <string>

namespace gomu
{

class Shader
{
public:
    Shader();
    ~Shader();

    void Load(std::string vertex_shader, std::string fragment_shader);
    void enable(bool enabled = false);

private:
    GLuint m_vs, m_fs, m_program;
};
}
