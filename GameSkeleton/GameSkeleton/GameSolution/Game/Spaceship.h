#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <sstream>
#include "Shape.h"

using std::stringstream;

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
	void DrawValue(Core::Graphics& g, int x, int y, float num);
	void DrawValue(Core::Graphics& g, int x, int y, int num);
	void DrawValue(Core::Graphics& g, int x, int y, Vector2 num);
};

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