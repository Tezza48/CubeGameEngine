#pragma once
#include "GLResource.h"
#include "Vertex.h"

class VertexArray :
	public GLResource
{
public:
	VertexArray();
	VertexArray(const VertexArray &) = delete;
	~VertexArray();

	void InitLayout(unsigned int count, const VertexElementDescription * descriptions);

	// Inherited via GLResource
	virtual void Bind() override;
	virtual void Unbind() override;
};

