#pragma once
#include "GLResource.h"
class GLVertexBuffer :
	public GLResource
{
public:
	GLVertexBuffer();
	~GLVertexBuffer();

	// Inherited via GLResource
	virtual void InitGLResource(const void * data) override;
	virtual void Bind() override;
	virtual void Unbind() override;
	//virtual ResourceHandle GetHandle() override;
};

