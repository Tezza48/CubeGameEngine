#pragma once
#include "GLResource.h"
class IndexBuffer :
	public GLResource
{
private:
	GLsizeiptr elementSize;
	unsigned long numIndices;
public:
	IndexBuffer() = delete;
	IndexBuffer(const IndexBuffer &) = delete; // Deal with copy ctor later
	IndexBuffer(GLsizeiptr size, const void * data, GLenum usage, unsigned long numIndices);
	~IndexBuffer();

	// Inherited via GLResource
	virtual void Bind() override;
	virtual void Unbind() override;

	unsigned long GetNumIndices() const;
	GLsizeiptr GetElementSize() const;
};

