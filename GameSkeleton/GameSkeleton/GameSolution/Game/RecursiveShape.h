#ifndef RECURSIVE_SHAPE_H
#define RECURSIVE_SHAPE_H

#include "Vector2.h"
#include "Matrix3.h"
#include "Shape.h"
using Engine::Matrix3;

class RecursiveShape
{
public:
	Matrix3 trans1, trans2, trans3;
	Shape shape1;
	Shape shape2;
	Shape shape3;
	float angle1, angle2, angle3, radianChange;
	Vector2 pos1, pos2, pos3;
	RecursiveShape();
	void draw(Core::Graphics&);
	void update(float dt);
};

#endif