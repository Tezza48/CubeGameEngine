#include "GLTexture.h"



GLTexture::GLTexture(unsigned int width, unsigned int height, 
	unsigned int bpp, unsigned char dimension, const void * data)
	: width(width), height(height), bpp(bpp)
{
	glGenTextures(1, &glHandle);
	switch (dimension)
	{
	//case 1:
	//	glTarget = GL_TEXTURE_1D;
	//	break;
	case 2:
		glTarget = GL_TEXTURE_2D;
		Bind();
		glTexImage2D(glTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateTextureMipmap(glHandle);
		break;
	//case 3:
	//	glTarget = GL_TEXTURE_3D;
	//	break;
	default:
		DebugLog("Unsupported Texture Dimension");
		break;
	}
	Unbind();
}


GLTexture::~GLTexture()
{
	glDeleteTextures(1, &glHandle);
}

void GLTexture::Bind()
{
	glBindTexture(glTarget, glHandle);
}

void GLTexture::Unbind()
{
	glBindTexture(glTarget, 0);
}

unsigned int GLTexture::GetWidth()
{
	return width;
}

unsigned int GLTexture::GetHeight()
{
	return height;
}

unsigned int GLTexture::GetNumPixels()
{
	return width * height;
}

//ResourceHandle GLTexture::GetHandle()
//{
//	return glHandle;
//}
