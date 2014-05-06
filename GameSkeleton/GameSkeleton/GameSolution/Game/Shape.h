#ifndef SHAPE_H
#define SHAPE_H

#include "Core.h"
#include "Vector2.h"
using Engine::Vector2;

class Shape
{	
public:
	Vector2 *shapePoints;
	unsigned int numOfPoints;
	Shape()
	{

	}

	Shape(Vector2 *shapePointsCtor, unsigned int numPointsCtor)
	{
		shapePoints = shapePointsCtor;
		numOfPoints = numPointsCtor;
	}
};

#endif