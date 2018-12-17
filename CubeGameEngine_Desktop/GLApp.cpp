#include "GLApp.h"

using namespace std;

GLApp::GLApp(string title = "GL App") : windowTitle(title)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		puts("SDL Failed to Initialize");
		throw;
	}

	mainWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (!mainWindow)
	{
		puts("Failed To Create Widnow");
		throw;
	}

	int setAttrResult = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GLVersionMajor);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GLVersionMinor);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	if (setAttrResult < 0)
	{
		puts("Failed to Set Core GL Context Profile");
		throw;
	}

	context = SDL_GL_CreateContext(mainWindow);
	if (!context)
	{
		puts("Failed to Create GL Context");
		throw;
	}

	renderer = new Renderer();
}

GLApp::~GLApp()
{
	SafeDelete(renderer);
	SDL_Quit();
}

int GLApp::Run()
{
	renderer->Init();
	renderer->OnResize(AspectRatio());
	Start();
	isRunning = true;
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
			default:
				ProcessEvent(event);
				break;
			}
		}
		Update();
		renderer->Clear();
		Draw(renderer);
		SwapBuffers();
	}
	SafeDelete(renderer);
	return 0;
}

void GLApp::SwapBuffers()
{
	SDL_GL_SwapWindow(mainWindow);
	
}

void GLApp::SetBackgroundColor(const glm::vec4 & color)
{
	renderer->SetBackgroundColor(color);
}

float GLApp::AspectRatio() const
{
	return static_cast<float>(windowWidth) / windowHeight;
}

void GLApp::Quit()
{
	isRunning = false;
}
