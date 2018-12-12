#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct VertexPosition
{
	glm::vec3 position;
};

struct VertexPositionColor
{
	glm::vec3 position;
	glm::vec4 color;
};