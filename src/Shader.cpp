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

namespace
{
std::vector<char> readAll(const std::string filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        error("Could not open \"%s\" for reading.", filename.c_str());
    }
    file.seekg(0, std::ios_base::end);
    std::size_t size = file.tellg();
    file.seekg(0, std::ios_base::beg);
    std::vector<char> data(size + 1);
    file.read(data.data(), size);
    return data;
}
}

void Shader::Load(std::string vertex_shader, std::string fragment_shader)
{
    // Load shaders
    auto vertexCode = readAll(vertex_shader);
    auto fragmentCode = readAll(fragment_shader);

    const char *vSauce = vertexCode.data();
    const char *fSauce = fragmentCode.data();

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
