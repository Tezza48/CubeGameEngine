#pragma once
#include <glm/mat4x4.hpp>
#include "GLApp.h"
#include "GLTexture.h"
#include "Shader.h"

class VoxelSpriteTest :
	public GLApp
{
private:
	Shader * shader = nullptr;

	unsigned int meshVAO = 0;
	unsigned int meshVBuffer = 0;
	unsigned int meshIBuffer = 0;

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

