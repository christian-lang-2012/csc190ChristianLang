#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vector2.h"
#include "Core.h"
#include "ColorChangeType.h"
#include "Logger.h"

using Core::RGB;
using Engine::Vector2;

class Particle
{
public:
	Vector2 position, velocity;
	float lifetime, age, radius, angle;
	RGB currentColor;
	ColorChangeType colorChange;

	Particle();
	Particle(Vector2 pos, Vector2 vel, float lifetime, ColorChangeType type);

	void update(float);
	bool isAlive();


};

#endif
