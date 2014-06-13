#ifndef RECURSIVE_SHAPE_H
#define RECURSIVE_SHAPE_H

#include "Matrix3.h"
#include "Shape.h"
using Engine::Matrix3;

class RecursiveShape
{
public:
	Shape shape1;
	Shape shape2;
	Shape shape3;
	Matrix3 trans1, trans2, trans3;
	Vector2 pos1, pos2, pos3;
	float angle1, angle2, angle3, radianChange;
	
	RecursiveShape();
	void draw(Core::Graphics&);
	void update(float dt);
};

#endif