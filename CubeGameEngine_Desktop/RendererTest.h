#pragma once
#include "GLApp.h"
#include "GLTexture.h"

class RendererTest :
	public GLApp
{
private:
	GLTexture * texture;

public:
	RendererTest() : GLApp("Renderer Test") {}
	~RendererTest();


	// Inherited via GLApp
	virtual void Start() override;
	virtual void Update() override;
	virtual void ProcessEvent(const SDL_Event & event) override;
	virtual void Draw(Renderer * renderer) override;
};

