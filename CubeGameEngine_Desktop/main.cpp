#include "RendererTest.h"

#if _DEBUG
void DebugCleanup()
{
	system("PAUSE");
}
#endif // _DEBUG

int main(int argc, char**argv)
{
#if _DEBUG
	atexit(DebugCleanup);
#endif
	try
	{
		RendererTest app;
		return app.Run();
	}
	catch (void *)
	{
		puts("Exception Thrown\n");
	}
}
