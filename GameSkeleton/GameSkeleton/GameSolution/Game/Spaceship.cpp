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

Vector2 boundaryShapeHolder[] =
{
	Vector2(950.0f, 0.0f),
	Vector2(0.0f, 500.0f),
	Vector2(950.0f, 1000.0f),
	Vector2(1900.0f, 500.0f),

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

EnemySpaceship::EnemySpaceship()
{
	unsigned int enemyPoints = sizeof(enemyShipShape) / sizeof(*enemyShipShape);
	enemyShape = Shape(&enemyShipShape[0], enemyPoints);

	unsigned int travelPoints = sizeof(locationPoints) / sizeof(*locationPoints);
	travelPath = Shape(&locationPoints[0], travelPoints);
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

void EnemySpaceship::draw(Core::Graphics& g)
{
	for(unsigned int i = 0; i < enemyShape.numOfPoints; i++)
	{
		const Vector2& first = startingPosition + enemyShape.shapePoints[i];
		const Vector2& second = startingPosition + enemyShape.shapePoints[(i + 1) % enemyShape.numOfPoints];
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}

int locationCounter = 0;
float scale = 0;
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
	else
	{
		if(velocity.X > 0)
		{
			velocity.X -= offset;
		}
		if(velocity.Y > 0)
		{
			velocity.Y -= offset;
		}
		if(velocity.X < 0)
		{
			velocity.X += offset;
		}
		if(velocity.Y < 0)
		{
			velocity.Y += offset;
		}
		if(velocity.X ==0 && velocity.Y == 0)
		{
			velocity.X = 0;
			velocity.Y = 0;
		}
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
			velocity.Y *= -1;
		if(currentPosition.Y > 1000)
			velocity.Y *= -1;
	}
	if(boundaryType == 3)
	{
		for(unsigned int i = 0; i < numOfPoints2; i++)
		{
			Vector2 firstVertexPoint = tempBoundary.boundaryShape.shapePoints[i];
			Vector2 secondVertexPoint = tempBoundary.boundaryShape.shapePoints[(i+1) % numOfPoints2];
			Vector2 wallToShip = currentPosition - firstVertexPoint;

			float displacement = 30;
			displacement;

			if(currentPosition.X > 950 && currentPosition.Y < 500)
			{
				wallToShip.X += displacement;
				wallToShip.Y -= displacement;
			}
			if(currentPosition.X < 950 && currentPosition.Y < 500)
			{
				wallToShip.X -= displacement;
				wallToShip.Y -= displacement;
			}
			if(currentPosition.X > 950 && currentPosition.Y > 500)
			{
				wallToShip.X += displacement;
				wallToShip.Y += displacement;
			}
			if(currentPosition.X < 950 && currentPosition.Y > 500)
			{
				wallToShip.X -= displacement;
				wallToShip.Y += displacement;
			}


			Vector2 wall = secondVertexPoint - firstVertexPoint;
			Vector2 normalizedWall = wall.PerpCCW().Normalized();

			float dotProduct = Engine::Dot(wallToShip, normalizedWall);
			if(dotProduct >= 0 && dotProduct < 85)
			{
				velocity = velocity + (normalizedWall * (dotProduct * -2));
			}

			if(currentPosition.X < 0)
				velocity.X *= -1;
			if(currentPosition.X > 1900)
				velocity.X *= -1;
			if(currentPosition.Y < 0)
				velocity.Y *= -1;
			if(currentPosition.Y > 1000)
				velocity.Y *= -1;
		}
	}
}

void Spaceship::DrawValue(Core::Graphics& g, int x, int y, float num)
{
	stringstream ss;
	ss << "Height of The Screen: " << num;
	g.DrawString( x, y, ss.str().c_str());
}

void Spaceship::DrawValue(Core::Graphics& g, int x, int y, int num)
{
	stringstream ss;
	ss << "Boundary Type: " << num;
	g.DrawString( x, y, ss.str().c_str());
}

void Spaceship::DrawValue(Core::Graphics& g, int x, int y, Vector2 num)
{
	stringstream ss;
	ss << "Ship Position: " << num.X << ", " << num.Y;
	g.DrawString( x, y, ss.str().c_str());
}