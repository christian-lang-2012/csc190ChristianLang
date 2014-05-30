#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(float dragCoeff, float deceleration, ColorChangeType type, int numberParticles)
{
	drag = dragCoeff;
	deccel = deceleration;
	colorChange = type;
	numOfParticles = numberParticles;

	particles = new Particle[numberParticles];
}

ParticleEffect::~ParticleEffect()
{
	delete [] particles;
}

