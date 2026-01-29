#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() : mId(0) {};

void ShaderProgram::Unload()
{
    glDeleteProgram(mId);
}

void ShaderProgram::Compose(std::vector<Shader*> shaders)
{
    mId = glCreateProgram();
    //now attach shaders to use to the program
    for (int s = 0; s < shaders.size(); s++) {
        glAttachShader(mId, shaders[s]->GetID());
    }
    //and link it
    glLinkProgram(mId);
    Use();
}

unsigned int ShaderProgram::GetID()
{
    return mId;
}

void ShaderProgram::Use()
{
    glUseProgram(mId);
}

void ShaderProgram::setFloat(const GLchar* name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(mId, name), value);
}
void ShaderProgram::setInteger(const GLchar* name, GLint value)
{
    glUniform1i(glGetUniformLocation(mId, name), value);
}
void ShaderProgram::setVector2f(const GLchar* name, GLfloat x, GLfloat y)
{
    glUniform2f(glGetUniformLocation(mId, name), x, y);
}
void ShaderProgram::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(mId, name), x, y, z);
}
void ShaderProgram::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(mId, name), x, y, z, w);
}
