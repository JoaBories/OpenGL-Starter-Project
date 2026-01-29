#include "Shader.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;

std::string Shader::ReadFile(std::string filepath)
{
    std::string Shader;
    std::string line;

    //Open file of this name
    ifstream myFile;
    myFile.open(filepath);

    //Check for errors
    if (myFile.fail()) {
        cerr << "Error - Failed to open " << filepath << endl;
    }
    else
    {
        cout << "INFO - Success opening " << filepath << endl;
    }

    while (std::getline(myFile, line)) {
        Shader += line + "\n";
    }

    myFile.close();

    return Shader;
}

bool Shader::Compile(unsigned int shaderId)
{
    int retValue;
    glCompileShader(ID);
    glGetShaderiv(ID, GL_COMPILE_STATUS, &retValue);
    if (!retValue)
    {
        GLint len = 0;
        glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &len);
        std::vector <GLchar>log(len);

        glGetShaderInfoLog(ID, len, nullptr, log.data());
        cout << log.data() << endl;

        return false;
    }

    cout << "Compiled shader with no error" << endl;

    return true;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexString = ReadFile(vertexPath);
    const char* vertexCode = vertexString.c_str();
    std::string fragmentString = ReadFile(fragmentPath);
    const char* fragmentCode = fragmentString.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    Compile(vertex);
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    Compile(fragment);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
