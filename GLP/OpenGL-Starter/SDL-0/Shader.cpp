#include "Shader.h"
#include "glew.h"
#include <iostream>
#include <vector>

bool Shader::CompileShaderWithLog()
{
    int retValue;
    glCompileShader(mId);
    glGetShaderiv(mId, GL_COMPILE_STATUS, &retValue);
    if (!retValue)
    {
        GLint len = 0;
        glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &len);
        std::vector<GLchar>log(len);

        glGetShaderInfoLog(mId, len, nullptr, log.data());
        std::cout << log.data() << std::endl;

        return false;
    }

    std::cout << "Compiled shader with no error" << std::endl;

    return true;
}

Shader::Shader() : mId(0), mCode(""), mType(VERTEX) {}

Shader::Shader(int pId, std::string pCode, ShaderType pType) :mId(pId), mCode(pCode), mType(pType)
{
}

Shader::~Shader()
{
}

void Shader::Load(std::string pFilepath, ShaderType pShaderType)
{
    mType = pShaderType;

    mCode = ShaderFiles::ReadFile(pFilepath);

    switch (mType)
    {
    case VERTEX: {
        mId = glCreateShader(GL_VERTEX_SHADER);
        break;
    }
    case FRAGMENT: {
        mId = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }
    default:
    {
        std::cout << "This shader type has not yet been implemented." << std::endl;
        mId = glCreateShader(GL_VERTEX_SHADER);
        break;
    }
    }
    const char* source = mCode.c_str();
    glShaderSource(mId, 1, &source, NULL);
    
    CompileShaderWithLog();
}

std::string& Shader::GetCode()
{
	return mCode;
}
