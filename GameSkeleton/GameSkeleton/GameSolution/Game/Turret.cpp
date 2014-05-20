#include "Turret.h"

Vector2 turretBase[] =
{
	Vector2(-5.0f, -7.0f),
	Vector2(-5.0f, 4.0f),
	Vector2(5.0f, 4.0f),
	Vector2(5.0f, -7.0f)
};

Vector2 turretBarrel[] =
{
	Vector2(-2.50f, -22.0f),
	Vector2(-2.50f, -4.0f),
	Vector2(2.5f, -4.0f),
	Vector2(2.5f, -22.0f)
};

Turret::Turret()
{
	unsigned int numPoints1 = sizeof(turretBase) / sizeof(*turretBase);
	baseShape = Shape(&turretBase[0], numPoints1);
		
	numPoints1 = sizeof(turretBarrel) / sizeof(*turretBarrel);
	barrelShape = Shape(&turretBarrel[0], numPoints1);

}

Turret::Turret(Vector2 currentPosition)
{
	position = currentPosition;

	unsigned int numPoints1 = sizeof(turretBase) / sizeof(*turretBase);
	baseShape = Shape(&turretBase[0], numPoints1);
		
	numPoints1 = sizeof(turretBarrel) / sizeof(*turretBarrel);
	barrelShape = Shape(&turretBarrel[0], numPoints1);
}

void Turret::draw(Core::Graphics& g)
{
	for(unsigned int i = 0; i < baseShape.numOfPoints; i++)
	{
		const Vector2& first =  position + (transformationMatrix * baseShape.shapePoints[i]);
		const Vector2& second =  position + (transformationMatrix * baseShape.shapePoints[(i + 1) % baseShape.numOfPoints]);
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}

	for(unsigned int i = 0; i < barrelShape.numOfPoints; i++)
	{
		const Vector2& first =  position + (barrelTransform * barrelShape.shapePoints[i]);
		const Vector2& second =  position + (barrelTransform * barrelShape.shapePoints[(i + 1) % barrelShape.numOfPoints]);
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}

void Turret::update()
{
	int mouseX = Core::Input::GetMouseX();
	int mouseY = Core::Input::GetMouseY();
	Vector2 mouseVector((float) mouseX, (float) mouseY);
	Vector2 shipToMouseVector = position - mouseVector;
	Vector2 normalized = shipToMouseVector.Normalized();
	Matrix3 basisMatrix(normalized.PerpCW(), normalized);
	
	barrelTransform = basisMatrix;

}

Bullet Turret::fire()
{
	Bullet trajectory;
	trajectory.position = position;
	
	Vector2 newVelocity = barrelTransform * trajectory.velocity;
	
	trajectory.velocity.X = newVelocity.X;
	trajectory.velocity.Y = newVelocity.Y;

	trajectory.canBeDrawn = true;
	return trajectory;
}