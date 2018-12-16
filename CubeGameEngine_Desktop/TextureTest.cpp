#include "TextureTest.h"
#include "ShapeGenerator.h"
#include <glm/ext.hpp>
#include "vendor/stb_image/stb_image.h"

TextureTest::TextureTest(std::string title) : GLApp(title)
{
}

TextureTest::~TextureTest()
{
	SafeDelete(shader);
	SafeDelete(texture);
}

bool TextureTest::Init()
{
	GLApp::Init();

	auto mesh = ShapeGenerator::CreateUnitQuad();

	glGenVertexArrays(1, &meshVAO);
	glBindVertexArray(meshVAO);

	glGenBuffers(1, &meshVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshVBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPosition) * mesh.perVertex.size(),
		&mesh.perVertex[0], GL_STATIC_DRAW);

	glGenBuffers(1, &meshIBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * mesh.perIndex.size() ,
		&mesh.perIndex[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	shader = new Shader();
	shader->LoadShader("shader");

	projection = glm::perspective(glm::quarter_pi<float>(), AspectRatio(), 0.01f, 1000.0f);
	projection = glm::transpose(projection);


	// Load Texture
	stbi_set_flip_vertically_on_load(true);
	int x, y, n;
	unsigned char * data = stbi_load("res/smiley_2D.png", &x, &y, &n, 4);

	texture = new GLTexture(x, y, n, 2, data);
	stbi_image_free(data);
	texture->Unbind();

	return true;
}

int TextureTest::Run()
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

		shader->Use();

		glBindVertexArray(meshVAO);
		glBindBuffer(GL_ARRAY_BUFFER, meshVBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBuffer);
		
		glUniform1i(shader->GetUniformLocation("colorTexture"), 0);
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::transpose(view);
		glm::mat4 wvp = view * projection;
		auto loc = shader->GetUniformLocation("worldViewProj");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &wvp[0][0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		SwapBuffers();
	}
	return 0;
}
