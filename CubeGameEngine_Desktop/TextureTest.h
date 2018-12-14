#pragma once
#include "GLApp.h"
#include "GLTexture.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Utils.h"

class TextureTest :
	public GLApp
{
private:
	Shader * shader = nullptr;

	unsigned int meshVAO = 0;
	unsigned int meshVBuffer = 0;
	unsigned int meshIBuffer = 0;

	GLTexture * texture = nullptr;

	glm::mat4 projection;

public:
	TextureTest() : GLApp("Texture Test") {}
	TextureTest(std::string title);
	~TextureTest();
	bool Init() override;
	int Run() override;
};
