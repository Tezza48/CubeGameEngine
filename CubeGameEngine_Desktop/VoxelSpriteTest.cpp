#include "VoxelSpriteTest.h"

#include "ShapeGenerator.h"
#include <glm/ext.hpp>
#include "vendor/stb_image/stb_image.h"

VoxelSpriteTest::VoxelSpriteTest(std::string title) : GLApp(title)
{
}

VoxelSpriteTest::~VoxelSpriteTest()
{
	SafeDelete(shader);
	SafeDelete(texture);
}

bool VoxelSpriteTest::Init()
{
	GLApp::Init();

	auto mesh = ShapeGenerator::CreateUnitCubeFlat();

	glGenVertexArrays(1, &meshVAO);
	glBindVertexArray(meshVAO);

	glGenBuffers(1, &meshVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshVBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionNormal) * mesh.perVertex.size(),
		&mesh.perVertex[0], GL_STATIC_DRAW);

	glGenBuffers(1, &meshIBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * mesh.perIndex.size(),
		&mesh.perIndex[0], GL_STATIC_DRAW);

	for (GLuint i = 0; i < VertexPositionNormal::NumElements; i++)
	{		
		auto desc = VertexPositionNormal::ElementDescriptions[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, desc.size, desc.GetType(), desc.isNormalized, desc.stride, (void *)(desc.offset));
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	shader = new Shader();
	shader->LoadShader("sprite2D");

	projection = glm::perspective(glm::quarter_pi<float>(), AspectRatio(), 0.01f, 1000.0f);
	projection = glm::transpose(projection);


	// Load Texture
	stbi_set_flip_vertically_on_load(false);
	int x, y, n;
	unsigned char * data = stbi_load("res/Alien_01.png", &x, &y, &n, 4);

	texture = new GLTexture(x, y, n, 2);
	texture->InitGLResource(data);
	stbi_image_free(data);
	texture->Unbind();

	// Set AmbientColor
	ambientColor = glm::vec4(0.2f, 0.2f, 0.2f, 0.2f);
	auto amColLoc = shader->GetUniformLocation("ambientColor");
	shader->Use();
	glUniform4fv(amColLoc, 1, &ambientColor[0]);
	Shader::UnbindAll();

	return true;
}

int VoxelSpriteTest::Run()
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

		glClearColor(ambientColor.x, ambientColor.y, ambientColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Use();

		glBindVertexArray(meshVAO);
		glBindBuffer(GL_ARRAY_BUFFER, meshVBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBuffer);

		glUniform1i(shader->GetUniformLocation("colorTexture"), 0);
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		glm::vec3 eyePos(0.0f, 25.0f, 25.0f);

		glm::mat4 view = glm::lookAt(eyePos, glm::vec3(0.0), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::transpose(view);

		glm::mat4 world = glm::mat4(1.0);
		glm::mat4 wvp = view * projection;
		glm::mat4 wordInvTrans = glm::inverseTranspose(world);
		auto loc = shader->GetUniformLocation("worldViewProj");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &wvp[0][0]);
		loc = shader->GetUniformLocation("world");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &world[0][0]);
		loc = shader->GetUniformLocation("worldInvTranspose");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &wordInvTrans[0][0]);
		loc = shader->GetUniformLocation("eyePosW");
		glUniform3fv(loc, 1, &eyePos[0]);

		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, texture->GetNumPixels());
		SwapBuffers();
	}
	return 0;
}
