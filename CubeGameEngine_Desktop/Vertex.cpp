#include "Vertex.h"
#include <GL/glew.h>

int VertexElementDescription::GetType()
{
	switch (type)
	{
	case VertexElementDescription::Byte:
		return GL_BYTE;
	case VertexElementDescription::UnsignedByte:
		return GL_UNSIGNED_BYTE;
	case VertexElementDescription::Short:
		return GL_SHORT;
	case VertexElementDescription::UnsignedShort:
		return GL_UNSIGNED_SHORT;
	case VertexElementDescription::Int:
		return GL_INT;
	case VertexElementDescription::UnsignedInt:
		return GL_UNSIGNED_INT;
	case VertexElementDescription::HalfFloat:
		return GL_HALF_FLOAT;
	case VertexElementDescription::Float:
		return GL_FLOAT;
	case VertexElementDescription::Double:
		return GL_DOUBLE;
	case VertexElementDescription::Fixed:
		return GL_FIXED;
	default:
		return 0;
	}
}
