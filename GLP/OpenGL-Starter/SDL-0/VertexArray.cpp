#include "VertexArray.h"

VertexArray::VertexArray(float* pVertices, unsigned int pVerticeCount) :
	mVao(0), mVbo(0), mVerticeCount(pVerticeCount)
{
	glGenBuffers(1, &mVbo);

	//Create one ID to be given at object generation
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mVerticeCount * 6, pVertices, GL_STATIC_DRAW);

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}
