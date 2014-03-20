#include "gomu/Shader.hpp"

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
    //Load files
    std::ifstream inv(vertex_shader);
    std::ifstream inf(fragment_shader);
    if(!inv.is_open())
    {
        std::cout << "Failed to load " << vertex_shader << std::endl;
    }
    if(!inf.is_open())
    {
        std::cout << "Failed to load " << fragment_shader << std::endl;
    }

    char buffer[500];
    while(!inv.eof())
    {
        inv.getline(buffer, 500);
        vertexShader += buffer;
        vertexShader += "\n";
    }
    while(!inf.eof())
    {
        inf.getline(buffer, 500);
        fragmentShader += buffer;
        fragmentShader += "\n";
    }
    inv.close();
    inf.close();

    //Load shaders
    const char* vSauce = vertexShader.c_str();
    const char* fSauce = fragmentShader.c_str();

    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vSauce, nullptr);
    glShaderSource(fs, 1, &fSauce, nullptr);

    glCompileShader(vs);
    glCompileShader(fs);

    char errV[strlen(vSauce)];
    glGetShaderInfoLog(vs, strlen(vSauce), nullptr, errV);
    char errF[strlen(fSauce)];
    glGetShaderInfoLog(fs, strlen(vSauce), nullptr, errV);
    std::cout << "Compile status: \n" << errV << std::endl;
    std::cout << "Compile status: \n" << errF << std::endl;

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);
}

}
