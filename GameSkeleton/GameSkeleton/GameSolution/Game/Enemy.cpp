#include "Enemy.h"

Vector2 enemyBaseShape[] =
{
	Vector2(-10.0f, -10.0f),
	Vector2(-10.0f, 10.0f),
	Vector2(10.0f, 10.0f),
	Vector2(10.0f, -10.0f)
};

Enemy::Enemy()
{
	unsigned int numOfPoints = sizeof(enemyBaseShape) / sizeof(*enemyBaseShape);
	shape = Shape(&enemyBaseShape[0], numOfPoints);
	health = 1;
	scale = 0;
}

bool Enemy::isAlive()
{
	return health > 0;
}

bool Enemy::update(float dt, Vector2& playerShipPosition)
{
	if(playerShipPosition.X != position. X && playerShipPosition.Y != position.Y)
	{
		Vector2 lerpB = playerShipPosition;
		scale += .01f * dt * (1000/Engine::Length(lerpA, lerpB));

		position = Engine::Lerp(lerpA, lerpB, scale);

		if(scale > 1)
		{
			scale = 0;
		}
	}
	else
	{
		health--;
	}

	return isAlive();
}

void Enemy::draw(Core::Graphics& g)
{
	for(unsigned int i = 0; i < shape.numOfPoints; i++)
	{
		const Vector2& first = position + (shape.shapePoints[i]);
		const Vector2& second = position + (shape.shapePoints[(i + 1) % shape.numOfPoints]);
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}

void Enemy::setPosition(float x, float y)
{
	position.X = x;
	position.Y = y;
	lerpA = position;
}

Vector2 Enemy::getPosition()
{
	return position;
}