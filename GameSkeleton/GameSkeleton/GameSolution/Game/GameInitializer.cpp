#include "GameInitializer.h"
#include "AutoProfile.h"

GameInitializer::GameInitializer(void)
{
	LOG(Info, "Initializing game");
	SCREEN_WIDTH = 1900;
	SCREEN_HEIGHT = 1000;
	width = 1900;
	height = 1000;
	boudnaryTypeStuff = 1;
	bulletCounter = 0;
	isPress = false;
	constTimer = 0;

	profiler.AddCategory("Ship Collision Detection");
	profiler.AddCategory("Recursive Update");
	profiler.AddCategory("Particle Update");
	profiler.AddCategory("Bullet Update");
	profiler.AddCategory("Enemyships Update");

	profiler.AddCategory("Particle Draw");
}


GameInitializer::~GameInitializer(void)
{
}


bool GameInitializer::Update(float dt)
{
	fps = 1/dt;
	spf = dt;
	constTimer += dt;

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

	bool isCollision;
	{
		PROFILE("Ship Collision Detection");
		isCollision = mySpaceship.update(dt, boundary, boudnaryTypeStuff);
		enemySpaceship.update(dt);
		mySpaceship.turret.update();

	}

	if(isCollision)
	{
		ParticleEffect* explosion =new ExplosionEffect(0.30f, 0.02f, ColorChangeType::BUBBLE, mySpaceship.currentPosition, 1.0f, 10.0f, 500);
		system.AddEffect(explosion);
	}

	if(constTimer >= 3)
	{
		Enemy* e = new Enemy();
		float x = rando.RandomInRange(0, 1900);
		e->setPosition(x, 0.0f);
		enemySystem.AddEnemy(e);
		constTimer = 0;
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


	{
		PROFILE("Bullet Update");
		for(int i = 0; i < 100; i++)
		{
			if(globalBullets[i].canBeDrawn)
			{
				globalBullets[i].update(dt);
			}
		}
	}


	{
		for(int i = 0; i < 100; i++)
		{
			enemySystem.checkIfShipIsHit(globalBullets[i].position, system);
		}
	}

	{
		PROFILE("Enemyships Update");
		enemySystem.update(dt, mySpaceship.currentPosition);
	}

	{
		PROFILE("Recursive Update");
		rs.update(dt);
	}
	{
		PROFILE("Particle Update");
		system.Update(Input::IsPressed('W') || Input::IsPressed(Input::KEY_UP), -mySpaceship.rotationMatrixConstant, mySpaceship.currentPosition, dt);
	}

	bool shutDown = false;
	if(Input::IsPressed(Input::KEY_ESCAPE))
	{
		shutDown = true;
		profiler.WriteToFile();
		END_LOG	
	}

	return shutDown;

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
	graphics.DrawString(1500, 150, "FPS:");
	graphics.DrawString(1500, 165, "SPF:");
	Debug::Drawvalue(graphics, 1550, 165, spf);
	Debug::Drawvalue(graphics, 1550, 150, Debug::Debug_RoundValue(fps));


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

	enemySystem.draw(graphics);

	{
		PROFILE("Particle Draw");
		system.Draw(graphics);
	}
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

