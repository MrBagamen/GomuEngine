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
    GLuint program;

    void Load(std::string vertex_shader, std::string fragment_shader);
    void enable(bool enabled = false);
private:
    std::string vertexShader, fragmentShader;
    GLuint vs, fs;
};
}

#endif // SHADER_HPP
