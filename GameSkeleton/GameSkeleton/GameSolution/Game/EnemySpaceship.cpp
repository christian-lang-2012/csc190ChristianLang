#include "EnemySpaceship.h"

Vector2 enemyShipShape[] =
{
	Vector2(0.0f, -10.0f),
	Vector2(10.0f, 0.0f),
	Vector2(0.0f, 10.0f),
	Vector2(-10.0f, 0.0f)
};

Vector2 locationPoints[] =
{
	Vector2(300.0f, 100.0f),
	Vector2(100.0f, 100.0f),
	Vector2(300.0f, 300.0f),
	Vector2(100.0f, 300.0f)
};

int locationCounter = 0;
float scale = 0;

EnemySpaceship::EnemySpaceship()
{
	unsigned int enemyPoints = sizeof(enemyShipShape) / sizeof(*enemyShipShape);
	enemyShape = Shape(&enemyShipShape[0], enemyPoints);

	unsigned int travelPoints = sizeof(locationPoints) / sizeof(*locationPoints);
	travelPath = Shape(&locationPoints[0], travelPoints);
}

void EnemySpaceship::draw(Core::Graphics& g)
{
	for(unsigned int i = 0; i < enemyShape.numOfPoints; i++)
	{
		const Vector2& first = startingPosition + enemyShape.shapePoints[i];
		const Vector2& second = startingPosition + enemyShape.shapePoints[(i + 1) % enemyShape.numOfPoints];
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}


void EnemySpaceship::update(float dt)
{
	Vector2 lerpA = travelPath.shapePoints[locationCounter];
	Vector2 lerpB = travelPath.shapePoints[(locationCounter + 1) % 4];
	scale += .25f * dt * (1000/Engine::Length(lerpA, lerpB));

	startingPosition = Engine::Lerp(lerpA, lerpB, scale);

	if(scale >= 1)
	{
		locationCounter++;
		if(locationCounter == 4)
		{
			locationCounter = 0;
		}
		scale = 0;
		lerpA = lerpB;
		lerpB = travelPath.shapePoints[locationCounter];
	}
}