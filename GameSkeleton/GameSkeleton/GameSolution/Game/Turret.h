#ifndef TURRET_H
#define TURRET_H

#include "Matrix3.h"
#include "Shape.h"
#include "Bullet.h"

using Engine::Matrix3;

class Turret
{
public:
	Matrix3 transformationMatrix;
	Matrix3 barrelTransform;
	Shape barrelShape;
	Shape baseShape;
	Vector2 position;
	Turret();
	Turret(Vector2 currentPosition);

	void update();
	void draw(Core::Graphics&);
	Bullet fire();
};

#endif