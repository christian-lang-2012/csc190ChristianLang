#include "Bullet.h"

Vector2 bulletPoints[] =
{
	Vector2(-1.5f, -1.5f),
	Vector2(-1.5f, 1.5f),
	Vector2(1.5f, 1.5f),
	Vector2(1.5f, -1.5f)
};


Bullet::Bullet()
{
	acceleration = 700.0f;
	unsigned int numOfPoints = sizeof(bulletPoints) / sizeof(*bulletPoints);
	bulletShape = Shape(&bulletPoints[0], numOfPoints);
	canBeDrawn = false;
	velocity.X = 0.0f;
	velocity.Y = -300.0f;
}

void Bullet::update(float dt)
{
	Dt = dt;
}

void Bullet::draw(Core::Graphics& g)
{
	position = position + (velocity * Dt);
	if((position.X < 0 || position.X > 1000) && (position.Y > 1900 || position.Y < 0))
	{
		canBeDrawn = false;
	}

	if(canBeDrawn)
	{
		for(unsigned int i = 0; i < bulletShape.numOfPoints; i++)
		{
			const Vector2& first = position + (transformationMatrix * bulletShape.shapePoints[i]);
			const Vector2& second = position + (transformationMatrix *bulletShape.shapePoints[(i + 1) % bulletShape.numOfPoints]);
			g.DrawLine(first.X, first.Y, second.X, second.Y);
		}
	}
}