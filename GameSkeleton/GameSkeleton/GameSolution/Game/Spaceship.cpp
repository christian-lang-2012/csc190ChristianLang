#include "Spaceship.h"

int boundaryType = 1;
unsigned int numOfPoints2;

Vector2 shipShape[] =
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

Vector2 boundaryShapeHolder[] =
{
	Vector2(400.0f, 0.0f),
	Vector2(800.0f, 600.0f),
	Vector2(400.0f, 1000.0f),
	Vector2(0.0f, 600.0f),

};

Spaceship::Spaceship()
{
	unsigned int numPoints1 = sizeof(shipShape) / sizeof(*shipShape);
	spaceshipShape = Shape(&shipShape[0], numPoints1);
}


Boundary::Boundary()
{
	numOfPoints2 = sizeof(boundaryShapeHolder) / sizeof(*boundaryShapeHolder);
	boundaryShape = Shape(&boundaryShapeHolder[0], numOfPoints2);
}

void Boundary::draw(Core::Graphics& g)
{
	if(boundaryType == 3)
	{
		for(unsigned int i = 0; i < boundaryShape.numOfPoints; i++)
		{
			const Vector2& first = boundaryShape.shapePoints[i];
			const Vector2& second = boundaryShape.shapePoints[(i + 1) % boundaryShape.numOfPoints];
			g.DrawLine(first.X, first.Y, second.X, second.Y);
		}
	}
}


void Spaceship::draw(Core::Graphics& g)
{
	for(unsigned int i = 0; i < spaceshipShape.numOfPoints; i++)
	{
		const Vector2& first = currentPosition + spaceshipShape.shapePoints[i];
		const Vector2& second = currentPosition + spaceshipShape.shapePoints[(i + 1) % spaceshipShape.numOfPoints];
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}

void Spaceship::update(float dt, Boundary b, int boundaryTypeCtor = 1)
{
	Boundary tempBoundary = b;

	float offset = 150.0f * dt;
	boundaryType = boundaryTypeCtor;

	if(Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D'))
	{
		velocity.X += offset;
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A'))
	{
		velocity.X -= offset;
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W'))
	{
		velocity.Y -= offset;
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S'))
	{
		velocity.Y += offset;
	}
	
	currentPosition.X = currentPosition.X + velocity.X * dt;
	currentPosition.Y = currentPosition.Y + velocity.Y * dt;

	if(boundaryType == 1)
	{
		if(currentPosition.X < -60)
			currentPosition.X = 1960;
		if(currentPosition.X > 1960)
			currentPosition.X = -60;
		if(currentPosition.Y > 1060)
			currentPosition.Y = -60;
		if(currentPosition.Y < -60)
			currentPosition.Y = 1060;
	}
	if(boundaryType == 2)
	{
		if(currentPosition.X < 0)
			velocity.X *= -1;
		if(currentPosition.X > 1900)
			velocity.X *= -1;
		if(currentPosition.Y < 0)
			velocity.X *= -1;
		if(currentPosition.Y > 1000)
			velocity.X *= -1;
	}
	if(boundaryType == 3)
	{
		for(unsigned int i = 0; i < numOfPoints2; i++)
		{
			Vector2 firstVertexPoint = tempBoundary.boundaryShape.shapePoints[i];
			Vector2 secondVertexPoint = tempBoundary.boundaryShape.shapePoints[(i+1) % numOfPoints2];
			Vector2 wallToShip = currentPosition - firstVertexPoint;
			Vector2 wall = secondVertexPoint - firstVertexPoint;
			Vector2 normalizedWall = wall.PerpCCW().Normalized();
			float dotProduct = Engine::Dot(wallToShip, normalizedWall);
			if(dotProduct <= 0)
			{
				velocity = velocity + (normalizedWall * (dotProduct * -2));
			}
		}
	}
}