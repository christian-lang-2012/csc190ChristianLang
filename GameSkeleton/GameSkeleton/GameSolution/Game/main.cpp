#include "Engine.h"
#include "Spaceship.h"
#include "Core.h"
#include "EnemySpaceship.h"
#include "RecursiveShape.h"

using Core::Input;

Spaceship mySpaceship;
EnemySpaceship enemySpaceship;
Boundary boundary;

Bullet globalBullets[100];

RecursiveShape rs;

int SCREEN_WIDTH = 1900;
int SCREEN_HEIGHT = 1000;
float width = 1900;
float height = 1000;
int boudnaryTypeStuff = 1;
int bulletCounter = 0;
bool isPress = false;

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
	mySpaceship.turret.update();
	
	if(Input::IsPressed(Input::BUTTON_LEFT) && !isPress)
	{
		globalBullets[bulletCounter] = mySpaceship.turret.fire();
		isPress = true;

		if(bulletCounter == 99)
		{
			bulletCounter = 0;
		}
		bulletCounter++;
	}
	else if((Input::IsPressed(Input::BUTTON_LEFT) && isPress))
	{
		//do nothing
	}
	else if(!Input::IsPressed(Input::BUTTON_LEFT) && isPress)
	{
		isPress = false;
	}
	
	for(int i = 0; i < 100; i++)
	{
		if(globalBullets[i].canBeDrawn)
		{
			globalBullets[i].update(dt);
		}
	}

	rs.update(dt);

	return Input::IsPressed(Input::KEY_ESCAPE);

}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(1300, 10, "Use UP or W to move the ship forward.");
	graphics.DrawString(1300, 25, "Use A, D, LEFT, or RIGHT to rotate the ship."); 
	graphics.DrawString(1300, 40, "Use S or DOWN to move the ship backwards.");
	graphics.DrawString(1300, 55 , "Press These Buttons for Different Boundary Types:");
	graphics.DrawString(1300, 70, "1: Wrap");
	graphics.DrawString(1300, 85, "2: Bounce");
	graphics.DrawString(1300, 100, "3: Boundaries");


	mySpaceship.draw(graphics);
	mySpaceship.turret.draw(graphics);

	mySpaceship.DrawValue(graphics, 1300, 150, boudnaryTypeStuff);
	mySpaceship.DrawValue(graphics, 1300, 170, height);
	mySpaceship.DrawValue(graphics, 1300, 190, mySpaceship.currentPosition);
	mySpaceship.DrawValue(graphics, 1300, 300, mySpaceship.transformationMatrix);

	boundary.draw(graphics);
	enemySpaceship.draw(graphics);

	rs.draw(graphics);

	for(int i = 0; i < 100; i++)
	{
		if(globalBullets[i].canBeDrawn)
		{
			globalBullets[i].draw(graphics);
		}
	}
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

