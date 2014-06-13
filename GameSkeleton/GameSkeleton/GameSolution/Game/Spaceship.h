#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <sstream>
#include "Turret.h"

using std::stringstream;
using Engine::Matrix3;

class Boundary
{
public:
	Shape boundaryShape;

	Boundary();

	void draw(Core::Graphics&);
};

class Spaceship
{
public:
	Turret turret;
	Shape spaceshipShape;
	Matrix3 transformationMatrix;
	Vector2 startingPosition;
	Vector2 currentPosition;
	Vector2 velocity;
	Vector2 acceleration;
	int health;
	
	float rotationMatrixConstant;
	
	Spaceship();
	void draw(Core::Graphics&);
	bool update(float dt, Boundary b, int boundaryType);
	void DrawValue(Core::Graphics& g, int x, int y, float num);
	void DrawValue(Core::Graphics& g, int x, int y, int num);
	void DrawValue(Core::Graphics& g, int x, int y, Vector2 num);
	void DrawValue(Core::Graphics& g, int x, int y, Matrix3 matrix);
	void DrawVelocity(Core::Graphics& g, int x, int y);
	
};

#endif