#pragma once
#include "glew.h"

class VertexArray
{
private:
	unsigned int mVbo;
	unsigned int mVao;
	unsigned int mVerticeCount;

public:
	VertexArray(float* pVertices, unsigned int pVerticeCount);
	
	void Use() const { glBindVertexArray(mVao); };
	unsigned int GetVerticeCount() const { return mVerticeCount; };

};