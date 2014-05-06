#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Shape.h"

class Boundary
{
public:
	Boundary();
	Shape boundaryShape;

	void draw(Core::Graphics&);
};

class Spaceship
{
public:
	Spaceship();
	Shape spaceshipShape;
	Vector2 startingPosition;
	Vector2 currentPosition;
	Vector2 velocity;
	
	void draw(Core::Graphics&);
	void update(float dt, Boundary b, int boundaryType);
};


#endif