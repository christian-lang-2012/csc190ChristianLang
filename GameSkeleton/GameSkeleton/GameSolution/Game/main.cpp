#include "Engine.h"
#include "Spaceship.h"
#include "Core.h"

using Core::Input;


Spaceship mySpaceship;

int SCREEN_WIDTH = 1900;
int SCREEN_HEIGHT = 1000;
float width = 1900;
float height = 1000;

bool Update(float dt)
{
	dt;

	mySpaceship.update(dt);

	bool isPressed = Input::IsPressed(Input::KEY_ESCAPE);

	return isPressed;
}

void Draw(Core::Graphics& graphics)
{
	mySpaceship.draw(graphics);


	/*graphics.SetColor(RGB(255,255,255));
	graphics.DrawString(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 -50, "Hello World");
	graphics.DrawLine(10,01,400,300);*/
}



void main()
{
	mySpaceship.startingPosition = Vector2(width/2, height/2);
	mySpaceship.currentPosition = mySpaceship.startingPosition;
	Core::Init("Game Demo", SCREEN_WIDTH, SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
}

