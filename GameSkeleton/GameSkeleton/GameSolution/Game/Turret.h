#ifndef TURRET_H
#define TURRET_H

#include "Bullet.h"

class Turret
{
public:
	Shape barrelShape;
	Shape baseShape;
	Matrix3 transformationMatrix;
	Matrix3 barrelTransform;
	Vector2 position;
	
	Turret();
	Turret(Vector2 currentPosition);

	void update();
	void draw(Core::Graphics&);
	Bullet fire();
};

#endif