#pragma once
#include "GLResource.h"
class VertexBuffer :
	public GLResource
{
public:
	VertexBuffer() = delete;
	VertexBuffer(size_t size, const void * data, GLenum usage);
	~VertexBuffer();

	// Inherited via GLResource
	virtual void Bind() override;
	virtual void Unbind() override;
};

