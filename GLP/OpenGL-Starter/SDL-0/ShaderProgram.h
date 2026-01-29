#pragma once

#include "Shader.h"
#include <vector>
#include "glew.h"

class ShaderProgram
{
private:
	unsigned int mId;

public:
	ShaderProgram();
	~ShaderProgram() = default;
	void Unload();
	void Compose(std::vector<Shader*> shaders);

	unsigned int GetID();
	void Use();

	void setFloat(const GLchar* name, GLfloat value);
	void setInteger(const GLchar* name, GLint value);
	void setVector2f(const GLchar* name, GLfloat x, GLfloat y);
	void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
	void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
};

