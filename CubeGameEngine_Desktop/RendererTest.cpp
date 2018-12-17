#include "RendererTest.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "vendor/stb_image/stb_image.h"

using namespace std;
using chronoClock = std::chrono::high_resolution_clock;

RendererTest::~RendererTest()
{
	SafeDelete(texture);
}

void RendererTest::Start()
{
	int x, y, n;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load("res/alien_anim_01.png", &x, &y, &n, 4);
	texture = new GLTexture(x, y, n, 2, data);
	stbi_image_free(data);

	baseTime = chronoClock::now();

	SetBackgroundColor(glm::vec4(0.5f, 0.5f, 0.6f, 1.0f));
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
	glm::mat4 world = glm::identity<glm::mat4>();
	world = glm::translate(world, glm::vec3(0.0f, 0.0f, 0.0f));
	chronoClock::time_point nowTime = chronoClock::now();
	auto dur = chrono::duration<float>(nowTime - baseTime);

	float seconds = dur.count();

	int seci = (int)seconds;

	renderer->DrawTexture(texture, glm::transpose(world), glm::vec3(0.0f, 0.0f, 32.0f), seci % 2);
}
