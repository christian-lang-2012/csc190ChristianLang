#ifndef BULLET_H
#define BULLET_H

#include "Core.h"
#include "Shape.h"
#include "Matrix3.h"

using Engine::Vector2;
using Engine::Matrix3;

class Bullet
{
public:
	Shape bulletShape;
	Vector2 position;
	Vector2 velocity;
	Matrix3 transformationMatrix;
	float acceleration;
	bool canBeDrawn;
	float Dt;

	Bullet();
	void update(float dt);
	void draw(Core::Graphics&);
};

#endif