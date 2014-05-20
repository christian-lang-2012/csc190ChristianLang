#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACEHIP_H

#include "Shape.h"


class EnemySpaceship
{
public:
	EnemySpaceship();
	Vector2 startingPosition;
	Shape enemyShape;
	Shape travelPath;
	void draw(Core::Graphics&);
	void update(float dt);
};

#endif