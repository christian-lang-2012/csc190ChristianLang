#include "GameInitializer.h"

GameInitializer::GameInitializer(void)
{
	SCREEN_WIDTH = 1900;
	SCREEN_HEIGHT = 1000;
	width = 1900;
	height = 1000;
	boudnaryTypeStuff = 1;
	bulletCounter = 0;
	isPress = false;
}


GameInitializer::~GameInitializer(void)
{
}


bool GameInitializer::Update(float dt)
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

	

	bool isCollision = mySpaceship.update(dt, boundary, boudnaryTypeStuff);
	enemySpaceship.update(dt);
	mySpaceship.turret.update();

	if(isCollision)
	{
		ParticleEffect* explosion =new ExplosionEffect(0.30f, 0.02f, ColorChangeType::FIRE, mySpaceship.currentPosition, 1.0f, 10.0f, 3000);
		system.AddEffect(explosion);
	}
	
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
	system.Update(Input::IsPressed('W') || Input::IsPressed(Input::KEY_UP), -mySpaceship.rotationMatrixConstant, mySpaceship.currentPosition, dt);

	return Input::IsPressed(Input::KEY_ESCAPE);

}

void GameInitializer::Draw(Core::Graphics& graphics)
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
	mySpaceship.DrawVelocity(graphics, 1300, 250);
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

	system.Draw(graphics);
}

void GameInitializer::Init()
{
	mySpaceship.startingPosition = Vector2(width/2, height/2);
	mySpaceship.currentPosition = mySpaceship.startingPosition;
	
	BubbleEffect* bubbles = new BubbleEffect(0.01f, 0.01f, ColorChangeType::FIRE, 
		Vector2(110, 110), 0.01f, 0.01f, 3.0f, 6.0f, 0.5f, 2.5f, 60);
	system.AddEffect(bubbles);

	enemySpaceship.startingPosition = Vector2(300, 100);

	Core::Init("Lang Game", SCREEN_WIDTH, SCREEN_HEIGHT);
}

