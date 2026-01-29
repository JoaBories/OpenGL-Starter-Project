#include "VertexArray.h"

#include <SDL.h>
#include <glew.h>

VertexArray::VertexArray(const float* pVertices, unsigned int pVerticeCount, const unsigned int* pIndices, unsigned int pIndexCount, bool pVertexColor) :
    mVerticeCount(pVerticeCount), mIndexCount(pIndexCount), mVertexArrayId(0), mVertexBufferId(0), mIndexBufferId(0)
{
    //Generate VAO
    glGenVertexArrays(1, &mVertexArrayId);
    glBindVertexArray(mVertexArrayId);

    //Generate VBO
    glGenBuffers(1, &mVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 3 * sizeof(float), pVertices, GL_STATIC_DRAW);

    //Generate Index Buffer
    glGenBuffers(1, &mIndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount * sizeof(float), pIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    if (pVertexColor)
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    }
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVertexBufferId);
    glDeleteBuffers(1, &mIndexBufferId);
    glDeleteBuffers(1, &mVertexArrayId);
}

void VertexArray::SetActive()
{
    glBindVertexArray(mVertexArrayId);
}
