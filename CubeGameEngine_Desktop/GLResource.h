#pragma once
#include <GL/glew.h>
#include "GLApp.h"

typedef unsigned int ResourceHandle;
typedef unsigned int ResourceTarget;

class GLResource
{
protected:
	ResourceHandle glHandle;
	ResourceTarget glTarget;
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	ResourceHandle GetHandle() const
	{
		return glHandle;
	}
};