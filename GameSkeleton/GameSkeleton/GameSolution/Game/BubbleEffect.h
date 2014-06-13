#ifndef BUBBLE_EFFECT_H
#define BUBBLE_EFFECT_H

#include "ParticleEffect.h"

const float MIN_LIFETIME = 0.0f;
const float MAX_LIFETIME = 3.0f;

const float MIN_R_DEFAULT = 1.5f;
const float MAX_R_DEFAULT = 15.0f;
const float MIN_VEL1 = 0.001f;

class BubbleEffect : public ParticleEffect
{
public:
	Vector2 position;
	Randomizer rn;
	float minVelocity, maxVelocity, angle, variance, minRadius, maxRadius;
	bool isThrusting;
	
	void Draw_MidpointCircle(Core::Graphics& graphics, float radius, Vector2 position);
	BubbleEffect(float dragCoeff1, float decceleration1, ColorChangeType type1, Vector2 startPos1, float variance1, float angle1, float minVel1, float maxVel1, float minR1 = MIN_R_DEFAULT, float maxR1 = MAX_R_DEFAULT, int numberOfParticles = 1000)
		: ParticleEffect(dragCoeff1, decceleration1, type1, numberOfParticles)
	{
		position = startPos1;
			minVelocity = minVel1;
			maxVelocity = maxVel1;
			angle = angle1;
			variance = variance1;

			minRadius = minR1;
			maxRadius = maxR1;
	}

	void draw(Core::Graphics&);
	bool update(bool isThrusting1, float angle1, Vector2 pos1, float dt);
	bool update(float dt);

};

#endif