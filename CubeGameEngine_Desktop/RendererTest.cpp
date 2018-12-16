#include "RendererTest.h"
#include "vendor/stb_image/stb_image.h"

using namespace std;

RendererTest::~RendererTest()
{
	SafeDelete(texture);
}

void RendererTest::Start()
{
	int x, y, n;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load("res/Alien_01.png", &x, &y, &n, 4);
	texture = new GLTexture(x, y, n, 2, data);
	stbi_image_free(data);
}

void RendererTest::Update()
{
}

void RendererTest::ProcessEvent(const SDL_Event & event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				Quit();
				return;
		}
	default:
		return;
	}
}

void RendererTest::Draw(Renderer * renderer)
{
	renderer->DrawTexture(texture, glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -20.0f));
}
