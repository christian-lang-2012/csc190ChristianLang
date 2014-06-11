#include "Spaceship.h"

unsigned int numOfPoints2;
int boundaryType = 1;

Vector2 shipShape[] =
{
	Vector2(0.0f, -30.0f) * 1.4f,
	Vector2(-3.0f, -15.0f) * 1.4f,
	Vector2(-9.0f, 0.0f)  * 1.4f,
	Vector2(-3.0f, 3.0f)  * 1.4f,
	Vector2(-15.0f, 15.0f) * 1.4f,
	Vector2(0.0f, 6.0f) * 1.4f,
	Vector2(15.0f, 15.0f) * 1.4f,
	Vector2(3.0f, 3.0f) * 1.4f,
	Vector2(9.0f, 0.0f) * 1.4f,
	Vector2(3.0f, -15.0f) * 1.4f

};

Vector2 boundaryShapeHolder[] =
{
	Vector2(950.0f, 0.0f),
	Vector2(0.0f, 500.0f),
	Vector2(950.0f, 1000.0f),
	Vector2(1900.0f, 500.0f),

};


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

Spaceship::Spaceship()
{
	unsigned int numPoints1 = sizeof(shipShape) / sizeof(*shipShape);
	spaceshipShape = Shape(&shipShape[0], numPoints1);
	rotationMatrixConstant = .2f;
	acceleration = Vector2(0.0f, 0.0f);
	health = 15;
}

void Spaceship::draw(Core::Graphics& g)
{
	for(unsigned int i = 0; i < spaceshipShape.numOfPoints; i++)
	{
		const Vector2& first =  currentPosition + (transformationMatrix * spaceshipShape.shapePoints[i]);
		const Vector2& second =  currentPosition + (transformationMatrix * spaceshipShape.shapePoints[(i + 1) % spaceshipShape.numOfPoints]);
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}

bool Spaceship::update(float dt, Boundary b, int boundaryTypeCtor = 1)
{
	LOG(Info, "Updating ships place");
	Boundary tempBoundary = b;

	boundaryType = boundaryTypeCtor;
	acceleration = Vector2();
	if(Core::Input::IsPressed(Core::Input::KEY_RIGHT) || Core::Input::IsPressed('D'))
	{
		rotationMatrixConstant += .1f;
		transformationMatrix = transformationMatrix.Rotation(rotationMatrixConstant);
		turret.transformationMatrix = transformationMatrix;
		
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_LEFT) || Core::Input::IsPressed('A'))
	{
		rotationMatrixConstant -= .1f;
		transformationMatrix = transformationMatrix.Rotation(rotationMatrixConstant);
		turret.transformationMatrix = transformationMatrix;		
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_UP) || Core::Input::IsPressed('W'))
	{
		acceleration.Y = -1.0f;
	}
	else if(Core::Input::IsPressed(Core::Input::KEY_DOWN) || Core::Input::IsPressed('S'))
	{
		acceleration.Y = 1.0f;
	}

	acceleration = transformationMatrix * acceleration;

	velocity = velocity + acceleration;
	currentPosition.X = currentPosition.X + velocity.X * dt;
	currentPosition.Y = currentPosition.Y + velocity.Y * dt;

	turret.position.X = currentPosition.X + velocity.X * dt;
	turret.position.Y = currentPosition.Y + velocity.Y * dt;


	if(boundaryType == 1)
	{
		if(currentPosition.X < -60)
		{
			currentPosition.X = 1960;
			turret.position.X = 1960;
		}
		if(currentPosition.X > 1960)
		{
			currentPosition.X = -60;
			turret.position.X = -60;
		}
		if(currentPosition.Y > 1060)
		{
			currentPosition.Y = -60;
			turret.position.Y = -60;
		}
		if(currentPosition.Y < -60)
		{
			currentPosition.Y = 1060;
			turret.position.Y = 1060;
		}
	}
	if(boundaryType == 2)
	{
		if(currentPosition.X < 0)
		{
			velocity.X *= -1;
			return true;
		}
		if(currentPosition.X > 1900)
		{
			velocity.X *= -1;
			return true;
		}
		if(currentPosition.Y < 0)
		{
			velocity.Y *= -1;
			return true;
		}
		if(currentPosition.Y > 1000)
		{
			velocity.Y *= -1;
			return true;
		}
	}
	if(boundaryType == 3)
	{
		for(unsigned int i = 0; i < numOfPoints2; i++)
		{
			Vector2 firstVertexPoint = tempBoundary.boundaryShape.shapePoints[i];
			Vector2 secondVertexPoint = tempBoundary.boundaryShape.shapePoints[(i+1) % numOfPoints2];
			Vector2 wallToShip = currentPosition - firstVertexPoint;

			float displacement = 30;

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
				return true;
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
	
	return false;
}

void Spaceship::DrawVelocity(Core::Graphics& g, int x, int y)
{
	stringstream ss;
	ss << "Velocity: " << velocity.X << ", " << velocity.Y;
	g.DrawString( x, y, ss.str().c_str());
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

void Spaceship::DrawValue(Core::Graphics& g, int x, int y, Matrix3 matrix)
{
	stringstream ss;
	ss << matrix.x1;
	g.DrawString(x, y, ss.str().c_str());

	ss = stringstream();
	ss << matrix.x2;
	g.DrawString(x + 100, y, ss.str().c_str());

	ss = stringstream();
	int temp = (int)(currentPosition.X) * 1000;
	float temp2 = (float) (temp / 1000);
	ss << temp2;
	g.DrawString(x + 220, y, ss.str().c_str());

	ss = stringstream();
	ss << matrix.y1;
	g.DrawString(x, y + 30, ss.str().c_str());
	
	ss = stringstream();
	ss << matrix.y2;
	g.DrawString(x + 100, y + 30, ss.str().c_str());
	
	ss = stringstream();
	temp = (int)(currentPosition.Y) * 1000;
	temp2 = (float) (temp / 1000);
	ss << temp2;
	g.DrawString(x + 220, y + 30, ss.str().c_str());
	
	ss = stringstream();

	ss <<  matrix.z1;
	g.DrawString(x, y + 60, ss.str().c_str());

	ss = stringstream();
	ss << matrix.z2;
	g.DrawString(x + 100, y + 60, ss.str().c_str());
	
	ss = stringstream();
	ss << matrix.z3;
	g.DrawString(x + 220, y + 60, ss.str().c_str());

}
