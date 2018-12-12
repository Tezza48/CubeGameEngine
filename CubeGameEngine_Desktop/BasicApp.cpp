#include "BasicApp.h"
#include "ShapeGenerator.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "vendor/stb_image/stb_image.h"

BasicApp::BasicApp(std::string title) : SDLGLApp::SDLGLApp(title)
{
	
}


BasicApp::~BasicApp()
{
	
}

bool BasicApp::Init()
{
	SDLGLApp::Init();

	// Generate Cube Mesh Data
	auto cubeMesh = ShapeGenerator::CreateUnitCube();
	auto quadMesh = ShapeGenerator::CreateUnitQuad();

	// Init GL Buffers (would be nice to abstract buffer stuff)
	glGenVertexArrays(1, &meshVAO);
	glBindVertexArray(meshVAO);

	glGenBuffers(1, &meshVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshVBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPosition) * 4,
		&quadMesh.perVertex[0], GL_STATIC_DRAW);

	glGenBuffers(1, &meshIBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 6,
		&quadMesh.perIndex[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// New Load Shader
	shader.LoadShader("shader");

	projection = glm::perspective(glm::quarter_pi<float>(), AspectRatio(), 0.01f, 1000.0f);
	projection = glm::transpose(projection);

	// Load Texture and Bind it to texture 0 in the shader
	int x, y, n;
	unsigned char * data = stbi_load("res/smiley_2D.png", &x, &y, &n, 4);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Set Uniforms
	shader.Use();
	glUniform1i(shader.GetUniformLocation("colorTexture"), 0);
	Shader::UnbindAll();
	return true;
}

int BasicApp::Run()
{
	bool isRunning = true;
	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				}
			}
		}
		glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		glBindVertexArray(meshVAO);
		glBindBuffer(GL_ARRAY_BUFFER, meshVBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBuffer);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindSampler(0, 0);

		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::transpose(view);

		glm::mat4 wvp = view * projection;

		auto loc = glGetUniformLocation(shader.GetProgram(), "worldViewProj");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(wvp));
		//loc = glGetUniformLocation(shader.GetProgram(), "sprite");

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		//glDrawElementsInstanced(GL_TRIANGLES, numQuadIndices, GL_UNSIGNED_SHORT, 0, 16 * 16);
		//glDrawRangeElementsBaseVertex(GL_TRIANGLES, quadIStart, quadIStart + numQuadIndices, numQuadIndices, GL_UNSIGNED_SHORT, 0, quadVStart);
		SDL_GL_SwapWindow(mainWindow);
	}
	SDL_Quit();
	return 0;
}
