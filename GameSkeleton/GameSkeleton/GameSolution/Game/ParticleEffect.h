#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include "Particle.h"

class ParticleEffect
{
public:
	Particle* particles;
	ColorChangeType colorChange;
	float drag, deccel;
	int numOfParticles;

	ParticleEffect(float dragCoeff, float deceleration, ColorChangeType type, int numberParticles);
	~ParticleEffect();

	virtual bool update(float dt) = 0;
	virtual bool update(bool isThrusting1, float angle1, Vector2 pos1, float dt) = 0;
	virtual void draw(Core::Graphics& graphics) = 0;
};

#endif