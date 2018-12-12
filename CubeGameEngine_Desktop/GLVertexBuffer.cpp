#include "GLVertexBuffer.h"



GLVertexBuffer::GLVertexBuffer()
{
}


GLVertexBuffer::~GLVertexBuffer()
{
}

void GLVertexBuffer::InitGLResource(const void * data)
{
	glCreateBuffers(1, &glHandle);
}

void GLVertexBuffer::Bind()
{
	glBindBuffer(glTarget, glHandle);
}

void GLVertexBuffer::Unbind()
{
	glBindBuffer(glTarget, 0);
}
