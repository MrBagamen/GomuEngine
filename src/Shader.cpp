#include "gomu/Shader.hpp"
#include "error.hpp"

#include <vector>
#include <iostream>
#include <fstream>

namespace gomu
{

Shader::Shader()
{
}

Shader::~Shader()
{
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(program);
}

void Shader::Load(std::string vertex_shader, std::string fragment_shader)
{
    // Load files
    std::ifstream inv(vertex_shader);
    std::ifstream inf(fragment_shader);

    if (!inv)
    {
        error("Failed to load \"%s\"", vertex_shader.c_str());
    }
    if (!inf)
    {
        error("Failed to load \"%s\"", fragment_shader.c_str());
    }

    char buffer[500];
    while (!inv.eof())
    {
        inv.getline(buffer, 500);
        vertexShader += buffer;
        vertexShader += "\n";
    }
    while (!inf.eof())
    {
        inf.getline(buffer, 500);
        fragmentShader += buffer;
        fragmentShader += "\n";
    }
    inv.close();
    inf.close();

    // Load shaders
    const char *vSauce = vertexShader.c_str();
    const char *fSauce = fragmentShader.c_str();

    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vSauce, nullptr);
    glShaderSource(fs, 1, &fSauce, nullptr);

    glCompileShader(vs);
    glCompileShader(fs);

    GLint len;
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &len);
    std::vector<char> errV(len);
    glGetShaderInfoLog(vs, errV.size(), nullptr, errV.data());
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &len);
    std::vector<char> errF(len);
    glGetShaderInfoLog(fs, errF.size(), nullptr, errF.data());
    std::cout << "Compile status: \n" << errV.data() << std::endl;
    std::cout << "Compile status: \n" << errF.data() << std::endl;

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
}

void Shader::enable(bool enabled)
{
    if (!enabled)
    {
        glUseProgram(0);
        return;
    }
    glUseProgram(program);
}
}
