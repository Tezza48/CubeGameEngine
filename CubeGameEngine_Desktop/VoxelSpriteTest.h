#pragma once
#include <glm/mat4x4.hpp>
#include "GLApp.h"
#include "GLTexture.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class VoxelSpriteTest :
	public GLApp
{
private:
	Shader * shader = nullptr;

	VertexArray * vertexArrayObject = nullptr;
	VertexBuffer * vertexBuffer = nullptr;
	IndexBuffer * indexBuffer = nullptr;

	GLTexture * texture = nullptr;

	glm::mat4 projection;
	glm::vec4 ambientColor;

public:
	VoxelSpriteTest() : GLApp("Voxel Sprite Test") {}
	VoxelSpriteTest(std::string title);
	~VoxelSpriteTest();
	bool Init() override;
	int Run() override;
};

