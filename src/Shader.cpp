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
    glDetachShader(m_program, m_vs);
    glDetachShader(m_program, m_fs);
    glDeleteShader(m_vs);
    glDeleteShader(m_fs);
    glDeleteProgram(m_program);
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
        m_vertexShader += buffer;
        m_vertexShader += "\n";
    }
    while (!inf.eof())
    {
        inf.getline(buffer, 500);
        m_fragmentShader += buffer;
        m_fragmentShader += "\n";
    }
    inv.close();
    inf.close();

    // Load shaders
    const char *vSauce = m_vertexShader.c_str();
    const char *fSauce = m_fragmentShader.c_str();

    m_vs = glCreateShader(GL_VERTEX_SHADER);
    m_fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_vs, 1, &vSauce, nullptr);
    glShaderSource(m_fs, 1, &fSauce, nullptr);

    glCompileShader(m_vs);
    glCompileShader(m_fs);

    GLint len;
    glGetShaderiv(m_vs, GL_INFO_LOG_LENGTH, &len);
    std::vector<char> errV(len);
    glGetShaderInfoLog(m_vs, errV.size(), nullptr, errV.data());
    glGetShaderiv(m_fs, GL_INFO_LOG_LENGTH, &len);
    std::vector<char> errF(len);
    glGetShaderInfoLog(m_fs, errF.size(), nullptr, errF.data());
    std::cout << "Compile status: \n" << errV.data() << std::endl;
    std::cout << "Compile status: \n" << errF.data() << std::endl;

    m_program = glCreateProgram();
    glAttachShader(m_program, m_vs);
    glAttachShader(m_program, m_fs);
    glLinkProgram(m_program);
}

void Shader::enable(bool enabled)
{
    if (!enabled)
    {
        glUseProgram(0);
        return;
    }
    glUseProgram(m_program);
}
}
