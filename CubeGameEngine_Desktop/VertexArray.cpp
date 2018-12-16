#include "VertexArray.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &glHandle);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &glHandle);
}

void VertexArray::InitLayout(unsigned int count, const VertexElementDescription * descriptions)
{
	for (GLuint i = 0; i < count; i++)
	{
		auto desc = descriptions[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, desc.size, desc.GetType(), desc.isNormalized, desc.stride, (void *)(desc.offset));
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(glHandle);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
