#include "GameInitializer.h"

GameInitializer gi;

bool Update(float dt)
{
	bool ret = gi.Update(dt);
	return ret;
}

void Draw(Core::Graphics& graphics)
{
	gi.Draw(graphics);
}

void main()
{	
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	gi.Init();
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
}

