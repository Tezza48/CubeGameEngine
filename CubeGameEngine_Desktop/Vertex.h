#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct VertexElementDescription
{
	int size = 4;
	enum ElementType
	{
		Byte,
		UnsignedByte,
		Short,
		UnsignedShort,
		Int,
		UnsignedInt,
		HalfFloat,
		Float,
		Double,
		Fixed
	} type = Float;
	int GetType();
	bool isNormalized = false;
	int stride = 0;
	unsigned int offset = 0;
};

struct VertexPosition
{
	glm::vec3 position;
};

struct VertexPositionColor
{
	glm::vec3 position;
	glm::vec4 color;
};

struct VertexPositionNormal
{
	glm::vec3 position;
	glm::vec3 normal;
	static int const NumElements = 2;
	static constexpr VertexElementDescription ElementDescriptions[NumElements] = 
	{
		{3, VertexElementDescription::Float, false, 6 * 4, 0},
		{3, VertexElementDescription::Float, true, 6 * 4, 12}
	};
};