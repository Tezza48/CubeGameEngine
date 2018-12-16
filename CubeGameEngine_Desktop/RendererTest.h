#pragma once
#include "GLApp.h"
#include "GLTexture.h"
#include <chrono>

class RendererTest :
	public GLApp
{
private:
	GLTexture * texture;
	std::chrono::high_resolution_clock::time_point baseTime;
public:
	RendererTest() : GLApp("Renderer Test") {}
	~RendererTest();

	// Inherited via GLApp
	virtual void Start() override;
	virtual void Update() override;
	virtual void ProcessEvent(const SDL_Event & event) override;
	virtual void Draw(Renderer * renderer) override;
};

