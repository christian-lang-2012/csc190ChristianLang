#ifndef ENEMY_H
#define ENEMY_H

#include "Shape.h"

class Enemy
{
public:
	Shape shape;
	Vector2 position;
	Vector2 velocity;
	Vector2 lerpA;
	float acceleration, scale;
	int health;

	Enemy();
	bool isAlive();
	bool update(float dt, Vector2& playerShipPosition);
	void draw(Core::Graphics& g);
	void setPosition(float x, float y);
	Vector2 getPosition();
};

#endif