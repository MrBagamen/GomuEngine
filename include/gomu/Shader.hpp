#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <gomu/gomu.hpp>

namespace gomu
{

class Shader
{
public:
    Shader();
    ~Shader();

    void Load(std::string vertex_shader, std::string fragment_shader);
private:
    std::string vertexShader, fragmentShader;
    GLuint vs, fs, program;
};
}

#endif // SHADER_HPP
