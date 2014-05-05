#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Core.h"
#include "Vector2.h"
using Engine::Vector2;

class Spaceship
{
public:
	Vector2 startingPosition;
	Vector2 currentPosition;
	Vector2 velocity;
	void draw(Core::Graphics&);
	void update(float dt);
};


#endif