#include "Engine.h"
#include "Spaceship.h"
#include "Core.h"

using Core::Input;

Spaceship mySpaceship;
EnemySpaceship enemySpaceship;
Boundary boundary;

int SCREEN_WIDTH = 1900;
int SCREEN_HEIGHT = 1000;
float width = 1900;
float height = 1000;
int boudnaryTypeStuff = 1;

bool Update(float dt)
{
	dt;
	
	if(Input::IsPressed('1'))
	{
		boudnaryTypeStuff = 1;
	}
	else if(Input::IsPressed('2'))
	{
		boudnaryTypeStuff = 2;
	}
	else if(Input::IsPressed('3'))
	{
		boudnaryTypeStuff = 3;
	}

	mySpaceship.update(dt, boundary, boudnaryTypeStuff);
	enemySpaceship.update(dt);
	bool isPressed = Input::IsPressed(Input::KEY_ESCAPE);

	return isPressed;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(1300, 10, "Use W, A, S, D or UP, DOWN, LEFT, RIGHT to move the ship");
	graphics.DrawString(1300, 25 , "Press These Buttons for Different Boundary Types:");
	graphics.DrawString(1300, 35, "1: Wrap");
	graphics.DrawString(1300, 45, "2: Bounce");
	graphics.DrawString(1300, 55, "3: Boundaries");


	mySpaceship.draw(graphics);

	mySpaceship.DrawValue(graphics, 1300, 150, boudnaryTypeStuff);
	mySpaceship.DrawValue(graphics, 1300, 170, height);
	mySpaceship.DrawValue(graphics, 1300, 190, mySpaceship.currentPosition);

	boundary.draw(graphics);
	enemySpaceship.draw(graphics);
}

void main()
{
	mySpaceship.startingPosition = Vector2(width/2, height/2);
	mySpaceship.currentPosition = mySpaceship.startingPosition;
	
	enemySpaceship.startingPosition = Vector2(300, 100);

	Core::Init("Lang Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
}

