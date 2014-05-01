#include "Engine.h"
#include "Core.h"
using Core::Input;

int SCREEN_WIDTH = 1900;
int SCREEN_HEIGHT = 1000;

bool Update(float dt)
{
	dt;
	bool isPressed = Input::IsPressed(Input::KEY_ESCAPE);

	return isPressed;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(255,255,255));
	graphics.DrawString(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 -50, "Hello World");
	graphics.DrawLine(10,01,400,300);
}



void main()
{
	Core::Init("Game Demo", SCREEN_WIDTH, SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
}

