#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(size_t size, const void * data, GLenum usage)
{
	glGenBuffers(1, &glHandle);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	Unbind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &glHandle);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, glHandle);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
