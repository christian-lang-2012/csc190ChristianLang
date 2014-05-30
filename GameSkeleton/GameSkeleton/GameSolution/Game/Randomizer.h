#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <stdlib.h>
#include "Vector2.h"

using Engine::Vector2;
const float E = 2.718f;
const float PI = 3.14159265f;

class Randomizer
{
public:
	
	float RandomFloat();
	Vector2 RandomUnitVector();
	float RandomInRange(float min, float max);
	float GuassianFunc(float curveHeight, float peakPos, float steepness, float asym, float x);
	Vector2 RandomUnitVector(float angle, float variance);
	Vector2 RandomVelocity(float min, float max);
};

#endif