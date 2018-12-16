#pragma once
#include <SDL/SDL.h>
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <cstdio>
#include <memory>
#include <string>
#include "Renderer.h"
#include "Utils.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

class GLApp
{
private:
	const int GLVersionMajor = 4;
	const int GLVersionMinor = 6;
	SDL_GLContext context;
	SDL_Window * mainWindow;
	bool isRunning;
protected:
	std::string windowTitle;

	int windowWidth = 800;
	int windowHeight = 600;
public:

public:
	GLApp() = delete;
	GLApp(const GLApp & app) = delete;
	GLApp(std::string title);
	virtual ~GLApp();
	virtual int Run();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void ProcessEvent(const SDL_Event & event) = 0;
	virtual void Draw(Renderer * renderer) = 0;
private:
	void SwapBuffers();
protected:
	float AspectRatio() const;
	void Quit();
};

