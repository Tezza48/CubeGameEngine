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

	vertexArrayObject = new VertexArray();
	vertexArrayObject->Bind();

	vertexBuffer = new VertexBuffer(
		sizeof(VertexPositionNormal) * mesh.perVertex.size(),
		&mesh.perVertex[0], GL_STATIC_DRAW);

	indexBuffer = new IndexBuffer(sizeof(unsigned short) * mesh.perIndex.size(), &mesh.perIndex[0], GL_STATIC_DRAW);

	vertexBuffer->Bind();
	vertexArrayObject->InitLayout(VertexPositionNormal::NumElements, VertexPositionNormal::ElementDescriptions);

	vertexArrayObject->Unbind();
	vertexBuffer->Unbind();

	shader = new Shader();
	shader->LoadShader("sprite2D");

	projection = glm::perspective(glm::quarter_pi<float>(), AspectRatio(), 0.01f, 1000.0f);
	projection = glm::transpose(projection);


	// Load Texture
	stbi_set_flip_vertically_on_load(false);
	int x, y, n;
	unsigned char * data = stbi_load("res/Alien_01.png", &x, &y, &n, 4);

	texture = new GLTexture(x, y, n, 2, data);
	stbi_image_free(data);
	texture->Unbind();

	// Set AmbientColor
	ambientColor = glm::vec4(0.2f, 0.2f, 0.2f, 0.2f);
	shader->Use();
	shader->UniformFloat4Array("ambientColor", 1, &ambientColor[0]);
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

		vertexArrayObject->Bind();
		vertexBuffer->Bind();
		indexBuffer->Bind();

		shader->UniformInt("colorTexture", 0);
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		glm::vec3 eyePos(0.0f, 25.0f, 25.0f);

		glm::mat4 view = glm::lookAt(eyePos, glm::vec3(0.0), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::transpose(view);

		glm::mat4 world = glm::mat4(1.0);
		glm::mat4 wvp = view * projection;
		glm::mat4 wordInvTrans = glm::inverseTranspose(world);

		shader->UniformMatrix4Array("worldViewProj", 1, GL_FALSE, &wvp[0][0]);
		shader->UniformMatrix4Array("world", 1, GL_FALSE, &world[0][0]);
		shader->UniformMatrix4Array("worldInvTranspose", 1, GL_FALSE, &wordInvTrans[0][0]);
		shader->UniformFloat3Array("eyePosW", 1, &eyePos[0]);

		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, texture->GetNumPixels());
		SwapBuffers();
	}
	return 0;
}
