#include "GLApp.h"

using std::puts;
using std::string;

#if _DEBUG
bool GLApp::DEBUG_PAUSE_ON_EXIT = false;
#endif // _DEBUG

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	// strings for building the message
	const char * _source;
	const char * _type;
	const char * _severity;

	// parse the error source
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		_source = "GL";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "Window";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "Third-Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "User";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		_source = "Other";
		break;
	default:
		_source = "Unknown";
		break;
	}
	switch (type)
	{
		//case GL_:
		//	type = "";
		//	break;
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		_type = "Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		_type = "Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		_type = "Pop Group";
		break;
	case GL_DEBUG_TYPE_OTHER:
		_type = "Other";
		break;
	default:
		_type = "Unknown";
		break;
	}
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "Medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		_severity = "Low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "Notification";
		break;
	default:
		_severity = "Unknown";
		break;
	}

	fprintf(stderr, "GL CALLBACK|Source %s|Type %s (%d)|Severity %s|%s\n\n", _source, _type, id, _severity, message);
#if _DEBUG
	GLApp::DEBUG_PAUSE_ON_EXIT = true;
#endif // _DEBUG
}

GLApp::GLApp(string title) : windowTitle(title)
{
}

GLApp::~GLApp()
{
	SDL_Quit();
}

bool GLApp::Init()
{
	if (!InitSDL()) return false;
	if (!InitGL()) return false;
	return true;
}

bool GLApp::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		DebugLog("SDL Failed to Initialize");
		return false;
	}

	mainWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (!mainWindow)
	{
		DebugLog("Failed To Create Widnow");
		return false;
	}

	int setAttrResult = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GLVersionMajor);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GLVersionMinor);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	setAttrResult |= SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	if (setAttrResult < 0)
	{
		DebugLog("Failed to Set Core GL Context Profile");
		return false;
	}

	context = SDL_GL_CreateContext(mainWindow);
	if (!context)
	{
		DebugLog("Failed to Create GL Context");
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_TEXTURE_2D);

	return true;
}

bool GLApp::InitGL()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		DebugLog("glewInit() failed");
		return false;
	}


	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	return true;
}

void GLApp::SwapBuffers()
{
	SDL_GL_SwapWindow(mainWindow);
}

float GLApp::AspectRatio() const
{
	return static_cast<float>(windowWidth) / windowHeight;
}
