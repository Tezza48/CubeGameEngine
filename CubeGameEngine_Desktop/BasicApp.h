#pragma once
#include "GLApp.h"
#include "Vertex.h"
#include "Shader.h"
#include <glm/matrix.hpp>

class BasicApp :
	public SDLGLApp
{
	Shader shader;
	//unsigned int shaderProgram;

	unsigned int meshVAO;
	unsigned int meshVBuffer;
	unsigned int meshIBuffer;

	int numCubeVerts, numQuadVerts;
	int cubeVStart, quadVStart;
	int numCubeIndices, numQuadIndices;
	int cubeIStart, quadIStart;

	unsigned int texture;

	glm::mat4 projection;

public:
	BasicApp(std::string title);
	~BasicApp();
	bool Init() override;
	int Run() override;

private:
	//void LoadContent() override;
};

#if _DEBUG
void DebugCleanup()
{
	if(SDLGLApp::DEBUG_PAUSE_ON_EXIT) system("PAUSE");
}
#endif // _DEBUG

int main(int argc, char**argv)
{
#if _DEBUG
	atexit(DebugCleanup);
#endif
	BasicApp app("Basic App");
	if (!app.Init()) return 0;
	return app.Run();
}
