#pragma once
#include "GLApp.h"
#include "Vertex.h"
#include "Shader.h"
#include <glm/matrix.hpp>
#include "GLTexture.h"

class BasicApp :
	public GLApp
{
	Shader shader;
	//unsigned int shaderProgram;

	unsigned int meshVAO;
	unsigned int meshVBuffer;
	unsigned int meshIBuffer;

	int numCubeVerts, numQuadVerts;
	int cubeVStart, quadVStart;
	int numCubeIndices, numQuadIndices;
	int cubeIStart, quadIStart;
	// unsigned int texture;

	glm::mat4 projection;

public:
	BasicApp(std::string title);
	~BasicApp();
	bool Init() override;
	int Run() override;

private:
	//void LoadContent() override;
};
