#include "TextureTest.h"
#include "BasicApp.h"
#include "VoxelSpriteTest.h"

#if _DEBUG
void DebugCleanup()
{
	if (GLApp::DEBUG_PAUSE_ON_EXIT) system("PAUSE");
}
#endif // _DEBUG

int main(int argc, char**argv)
{
#if _DEBUG
	atexit(DebugCleanup);
#endif
	VoxelSpriteTest app;
	if (!app.Init()) return 0;
	return app.Run();
}
