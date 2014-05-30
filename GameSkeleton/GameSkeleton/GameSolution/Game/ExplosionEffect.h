#ifndef EXPLOSION_EFFECT_H
#define EXPLOSION_EFFECT_H

#include "ParticleEffect.h"
#include "Randomizer.h"

const float MIN_VEL = 0.001f;


class ExplosionEffect : public ParticleEffect
{
public:
	Vector2 position;
	float minVelocity, maxVelocity;
	Randomizer rn;

	ExplosionEffect(float dragCoeff, float decceleration, ColorChangeType type,
		Vector2 startPos, float minVel, float maxVel, int numberOfParticles = 1000)
		: ParticleEffect(dragCoeff, decceleration, type, numberOfParticles){
			position = startPos;
			minVelocity = minVel;
			maxVelocity = maxVel;

			for (int i = 0; i < numberOfParticles; i++){
				Vector2 velocity = rn.RandomVelocity(minVel, maxVel);
				float LIFETIME = rn.RandomInRange(0.25f, 1.0f);

				particles[i] = Particle(position, velocity, LIFETIME, type);
			}
	}

	void draw(Core::Graphics& g);
	bool update(bool isThrusting, float angle, Vector2 pos, float dt);
	bool update(float dt);
};

#endif