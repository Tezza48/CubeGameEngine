#include "GLTexture.h"



GLTexture::GLTexture(unsigned int width, unsigned int height, unsigned int bpp = 4, unsigned char dimension = 2)
	: width(width), height(height), bpp(bpp)
{
	switch (dimension)
	{
	//case 1:
	//	glTarget = GL_TEXTURE_1D;
	//	break;
	case 2:
		glTarget = GL_TEXTURE_2D;
		break;
	//case 3:
	//	glTarget = GL_TEXTURE_3D;
	//	break;
	default:
		DebugLog("Unsupported Texture Dimension");
		break;
	}
}


GLTexture::~GLTexture()
{
	glDeleteTextures(1, &glHandle);
}

void GLTexture::InitGLResource(const void * data)
{
	glGenTextures(1, &glHandle);
	Bind();
	switch (glTarget)
	{
	//case GL_TEXTURE_1D:
	//	glTexImage1D(glTarget, 0, GL_RGBA, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	break;
	case GL_TEXTURE_2D:
		glTexImage2D(glTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		break;
	}
}

void GLTexture::Bind()
{
	glBindTexture(glTarget, glHandle);
}

void GLTexture::Unbind()
{
	glBindTexture(glTarget, 0);
}

//ResourceHandle GLTexture::GetHandle()
//{
//	return glHandle;
//}
