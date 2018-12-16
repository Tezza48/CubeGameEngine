#pragma once
#include "GLResource.h"
class IndexBuffer :
	public GLResource
{
public:
	IndexBuffer() = delete;
	IndexBuffer(size_t size, const void * data, GLenum usage);
	~IndexBuffer();

	// Inherited via GLResource
	virtual void Bind() override;
	virtual void Unbind() override;
};

