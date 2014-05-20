#include "RecursiveShape.h"

Vector2 recursivePoints[] =
{
	Vector2(-70.0f, -70.0f),
	Vector2(-70.0f, 70.0f),
	Vector2(70.0f, 70.0f),
	Vector2(70.0f, -70.0f)
};

Vector2 recursivePoints2[] =
{
	Vector2(-70.0f, -70.0f) * .5f,
	Vector2(-70.0f, 70.0f) * .5f,
	Vector2(70.0f, 70.0f) * .5f,
	Vector2(70.0f, -70.0f) * .5f
};

Vector2 recursivePoints3[] =
{
	Vector2(-70.0f, -70.0f) *.25f,
	Vector2(-70.0f, 70.0f) * .25f,
	Vector2(70.0f, 70.0f) * .25f,
	Vector2(70.0f, -70.0f) * .25f
};

RecursiveShape::RecursiveShape()
{
	radianChange = .03f;
	angle1 = 0;
	angle2 = 0;
	angle3 = 0;
	pos1 = Vector2(250, 500);
	pos2 = Vector2(300, 500);
	pos3 = Vector2(350, 500);
	
	unsigned int numPoints = sizeof(recursivePoints) / sizeof(*recursivePoints);
	shape1 = Shape(&recursivePoints[0], numPoints);

	numPoints = sizeof(recursivePoints2) / sizeof(*recursivePoints2);
	shape2 = Shape(&recursivePoints2[0], numPoints);
	
	numPoints = sizeof(recursivePoints3) / sizeof(*recursivePoints3);
	shape3 = Shape(&recursivePoints3[0], numPoints);
}

void RecursiveShape::update(float dt)
{
	trans1 = Matrix3();
	trans2 = Matrix3();
	trans3 = Matrix3();
	angle1 += radianChange*dt*10;
	angle2 -= radianChange*dt*40;
	angle3 += radianChange*dt*50;

	trans1 = trans1.Rotation(angle1);
	Vector2 v1(-50, 0);
	trans2 = trans2.Translation(v1);
	trans2 = trans2 * trans2.Rotation(angle2);
	trans2 = trans2 * trans2.Translation(v1);
	Vector2 v2(-100, 0);
	trans3 = trans2.Translation(v2);
	trans3 = trans3 * trans2;
	trans3 = trans3 * trans3.Rotation(angle3);
	trans3 = trans3 * trans3.Translation(v2);
}

void RecursiveShape::draw(Core::Graphics& g)
{
	for(unsigned int i = 0; i < shape1.numOfPoints; i++)
	{
		const Vector2& first =  pos1 + (trans1 * shape1.shapePoints[i]);
		const Vector2& second =  pos1 + (trans1 * shape1.shapePoints[(i + 1) % shape1.numOfPoints]);
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
	for(unsigned int i = 0; i < shape2.numOfPoints; i++)
	{
		const Vector2& first =  pos2 + (trans2 * shape2.shapePoints[i]);
		const Vector2& second =  pos2 + (trans2 * shape2.shapePoints[(i + 1) % shape2.numOfPoints]);
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
	for(unsigned int i = 0; i < shape3.numOfPoints; i++)
	{
		const Vector2& first =  pos3 + (trans3 * shape3.shapePoints[i]);
		const Vector2& second =  pos3  + (trans3 * shape3.shapePoints[(i + 1) % shape3.numOfPoints]);
		g.DrawLine(first.X, first.Y, second.X, second.Y);
	}
}
