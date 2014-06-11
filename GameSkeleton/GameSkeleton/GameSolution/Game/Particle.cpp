#include "Particle.h"

Particle::Particle()
{
	age = 0.0f;
	lifetime = 0.0f;
}

Particle::Particle(Vector2 pos, Vector2 vel, float life, ColorChangeType type)
{
	position = pos;
	velocity = vel;
	lifetime = life;
	colorChange = type;

	age = 0.0f;
}

void Particle::update(float dt)
{
	LOG(Info, "Particle update");
	age += dt;
}

bool Particle::isAlive()
{
	return (age < lifetime);
}

