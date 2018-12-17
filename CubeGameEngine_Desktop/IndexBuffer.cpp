#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLsizeiptr size, const void * data, GLenum usage, unsigned long numIndices) : elementSize(size), numIndices(numIndices)
{
	glGenBuffers(1, &glHandle);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &glHandle);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glHandle);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned long IndexBuffer::GetNumIndices() const
{
	return numIndices;
}

GLsizeiptr IndexBuffer::GetElementSize() const
{
	return elementSize;
}
