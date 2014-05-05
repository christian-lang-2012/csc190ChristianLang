#include "Spaceship.h"


Vector2 shipPoints[] =
{
	Vector2(0.0f, -30.0f),
	Vector2(-3.0f, -15.0f),
	Vector2(-9.0f, 0.0f),
	Vector2(-3.0f, 3.0f),
	Vector2(-15.0f, 15.0f),
	Vector2(0.0f, 6.0f),
	Vector2(15.0f, 15.0f),
	Vector2(3.0f, 3.0f),
	Vector2(9.0f, 0.0f),
	Vector2(3.0f, -15.0f)

};

void Spaceship::draw(Core::Graphics& g)
{
	const unsigned int NUM_POINTS = sizeof(shipPoints) / sizeof(*shipPoints);
	for(unsigned int i = 0; i < NUM_POINTS; i++)
	{
		const Vector2& first = currentPosition + shipPoints[i];
		const Vector2& second = currentPosition + shipPoints[(i + 1) % NUM_POINTS];
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}

void Spaceship::update(float dt)
{
	dt;
	float offset = .5f;

	if(Core::Input::IsPressed(Core::Input::KEY_RIGHT))
	{
		velocity.X += offset;
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_LEFT))
	{
		velocity.X -= offset;
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_UP))
	{
		velocity.Y -= offset;
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_DOWN))
	{
		velocity.Y += offset;
	}

	currentPosition = currentPosition + velocity;

}