#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACEHIP_H

#include "Shape.h"

class EnemySpaceship
{
public:
	Shape enemyShape;
	Shape travelPath;
	Vector2 startingPosition;
	
	EnemySpaceship();
	void draw(Core::Graphics&);
	void update(float dt);
};

#endif