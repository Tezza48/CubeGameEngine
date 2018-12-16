#pragma once
#include "GLResource.h"
class GLTexture :
	public GLResource
{
private:
	unsigned int width, height, bpp;
public:
	GLTexture() = delete;
	GLTexture(unsigned int width, unsigned int height, unsigned int bpp, unsigned char dimension, const void * data);
	~GLTexture();

	// Inherited via GLResource
	virtual void Bind() override;
	virtual void Unbind() override;

	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetNumPixels();
};

