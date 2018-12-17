# Cube Game Engine
2D Game engine that renders sprites as 3D Cubes/Voxels.


To Use, Derive a class from `GLApp` and override `Start`, `Update`, `ProcessEvent` and `Draw`
```cpp
#include "GLApp.h"
class MyGame :
	public GLApp
{
public:
	MyGame() : GLApp("My Cube Game!") {}
	~MyGame();

	virtual void Start() override;
	virtual void Update() override;
	virtual void ProcessEvent(const SDL_Event & event) override;
	virtual void Draw(Renderer * renderer) override;
};

```

`Start()` Initialize your Textures here along with various game objects
`Update()` is called once per frame, Game Logic goes Here
`ProcessEvent()` is called every time an event happens in SDL (The library that deals with the window and other system stuff). Check for keypresses and mouse clicks/movement Here.
`Draw()` is where you draw things using the `Renderer`


Implement you `main` as follows:
```cpp
int main(int argc, char**argv)
{
	try
	{
		RendererTest app;
		return app.Run();
	}
	catch (void *)
	{
		puts("Exception Thrown\n");
		return -1;
	}
}
```

---

Draw your sprite with `Renderer::DrawTexture()`

You can change the backcround colour with `Renderer::SetBackgroundColor`

Feel free to tinker with the behind the scenes renderer and base App and even the shaders.

If you have any suggestions about how the engine works feel free to voice them!.