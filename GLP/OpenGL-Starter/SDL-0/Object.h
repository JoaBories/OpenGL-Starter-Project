#pragma once

#include "ShaderProgram.h"
#include "VertexArray.h"

class Object
{
private:
	VertexArray* mVao;
	ShaderProgram* mShader;

public:
	Object(VertexArray* pVao, ShaderProgram* pShader);
	~Object() = default;

	VertexArray* GetVertexArray() const { return mVao; };
	ShaderProgram* GetShaderProgram() const { return mShader; };
};

