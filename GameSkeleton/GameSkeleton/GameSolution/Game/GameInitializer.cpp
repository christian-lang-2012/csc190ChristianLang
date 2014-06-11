#include "GameInitializer.h"
#include "AutoProfile.h"

GameInitializer::GameInitializer(void)
{
	LOG(Info, "Initializing game");
	SCREEN_WIDTH = 1900;
	SCREEN_HEIGHT = 1000;
	width = 1900;
	height = 1000;
	boudnaryTypeStuff = 2;
	bulletCounter = 0;
	isPress = false;
	constTimer = 0;
	startTimer = 0;
	deathTimer = 0;
	killCounter = 0;

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

bool GameInitializer::UpdateIntro(float dt)
{
	startTimer += dt;
	return false;
}

bool GameInitializer::UpdateInGame(float dt)
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
		ParticleEffect* explosion =new ExplosionEffect(0.30f, 0.02f, ColorChangeType::BUBBLE, mySpaceship.currentPosition, 1.0f, 10.0f, 300);
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
			enemySystem.checkIfShipIsHit(globalBullets[i].position, system, killCounter);
		}
	}

	{
		PROFILE("Enemyships Update");
		enemySystem.update(dt, mySpaceship, system, killCounter);
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

bool GameInitializer::UpdateDeath(float dt)
{
	deathTimer += dt;
	return false;
}

bool GameInitializer::Update(float dt)
{
	bool con;
	if(startTimer < 10)
	{
		con = UpdateIntro(dt);
	}
	else if(mySpaceship.health > 0)
	{
		con = UpdateInGame(dt);
	}
	else
	{
		con = UpdateDeath(dt);
	}
	return con;
}

void GameInitializer::DrawIntro(Core::Graphics& graphics)
{
	graphics.DrawString(800, 400, "You have 15 health, last as long as you can");
	graphics.DrawString(800, 500, "Use UP or W to move the ship forward.");
	graphics.DrawString(800, 550, "Use A, D, LEFT, or RIGHT to rotate the ship."); 
	graphics.DrawString(800, 600, "Use S or DOWN to move the ship backwards.");
	graphics.DrawString(800, 650 , "Press These Buttons for Different Boundary Types:");
	graphics.DrawString(800, 700, "1: Wrap");
	graphics.DrawString(800, 750, "2: Bounce");
	graphics.DrawString(800, 800, "3: Boundaries");
}

void GameInitializer::DrawInGame(Core::Graphics& graphics)
{
	graphics.DrawString(1500, 90, "Health:");
	graphics.DrawString(1500, 100, "FPS:");
	graphics.DrawString(1500, 120, "SPF:");
	graphics.DrawString(1500, 140, "Kill Count:");
	Debug::Drawvalue(graphics, 1550, 90, mySpaceship.health);
	Debug::Drawvalue(graphics, 1600, 140, killCounter);
	Debug::Drawvalue(graphics, 1550, 100, spf);
	Debug::Drawvalue(graphics, 1550, 120, Debug::Debug_RoundValue(fps));


	mySpaceship.draw(graphics);
	mySpaceship.turret.draw(graphics);

	mySpaceship.DrawValue(graphics, 1300, 150, boudnaryTypeStuff);
	//mySpaceship.DrawValue(graphics, 1300, 170, height);
	//mySpaceship.DrawValue(graphics, 1300, 190, mySpaceship.currentPosition);
	//mySpaceship.DrawVelocity(graphics, 1300, 250);
	//mySpaceship.DrawValue(graphics, 1300, 300, mySpaceship.transformationMatrix);

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

void GameInitializer::DrawDeath(Core::Graphics& graphics)
{
	graphics.DrawString(900, 500, "You have died. The game will close soon.");
}

void GameInitializer::Draw(Core::Graphics& graphics)
{
	if(startTimer < 10)
	{
		DrawIntro(graphics);
	}
	else if (mySpaceship.health > 0)
	{
		DrawInGame(graphics);
	}
	else
	{
		DrawDeath(graphics);
	}
}

void GameInitializer::Init()
{
	ASSERT(1 == 2, "UNCOMMENT THIS TO MAKE IT RUN!");
	mySpaceship.startingPosition = Vector2(width/2, height/2);
	mySpaceship.currentPosition = mySpaceship.startingPosition;

	BubbleEffect* bubbles = new BubbleEffect(0.01f, 0.01f, ColorChangeType::FIRE, 
		Vector2(110, 110), 0.01f, 0.01f, 3.0f, 6.0f, 0.5f, 2.5f, 30);
	system.AddEffect(bubbles);

	enemySpaceship.startingPosition = Vector2(300, 100);

	Core::Init("Lang Game", SCREEN_WIDTH, SCREEN_HEIGHT);
}

