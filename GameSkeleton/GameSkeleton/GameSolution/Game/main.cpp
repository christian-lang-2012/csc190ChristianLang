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
{	gi.Init();
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
}

