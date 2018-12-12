#pragma once
#include "GLResource.h"
class GLTexture :
	public GLResource
{
private:
	unsigned int width, height, bpp;
public:
	GLTexture(unsigned int width, unsigned int height, unsigned int bpp, unsigned char dimension);
	~GLTexture();

	// Inherited via GLResource
	virtual void InitGLResource(const void * data) override;

	// Inherited via GLResource
	virtual void Bind() override;
	virtual void Unbind() override;
};

