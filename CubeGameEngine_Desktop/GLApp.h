#pragma once
#include <string>
#include <SDL/SDL.h>
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <cstdio>
#include "Utils.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#if _DEBUG
#define DebugLog(str) std::printf("%s. %s, %s line %d\n", str, __FILE__, __FUNCSIG__, __LINE__); GLApp::DEBUG_PAUSE_ON_EXIT = true;
#else
#define DebugLog(str)
#endif // _DEBUG


class GLApp
{
private:
	const int GLVersionMajor = 4;
	const int GLVersionMinor = 6;
protected:
	SDL_Window * mainWindow;
	SDL_GLContext context;
	std::string windowTitle;

	int windowWidth = 800;
	int windowHeight = 600;
public:
#if _DEBUG
	static bool DEBUG_PAUSE_ON_EXIT;
#endif // _DEBUG

public:
	GLApp() : windowTitle("GL App") {}
	GLApp(std::string title);
	GLApp(const GLApp & app) = delete;
	virtual ~GLApp();
	virtual bool Init();
	virtual int Run() = 0;
private:
	bool InitSDL();
	bool InitGL();
protected:
	void SwapBuffers();
	float AspectRatio() const;
};

