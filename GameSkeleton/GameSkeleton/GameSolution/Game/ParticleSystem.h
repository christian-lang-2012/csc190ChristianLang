#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "ParticleEffect.h"
#include <vector>

using std::vector;

class ParticleSystem
{
private:
	vector<ParticleEffect*> particleEffects;
public:
	void AddEffect(ParticleEffect* effect);
	void RemoveEffect(int index);

	void RemoveEffect(ParticleEffect* effect);

	void Update(bool isThrusting, float angle, Vector2 pos, float dt);
	void Draw(Core::Graphics& graphics);
	void UpdateColors(ColorChangeType type, Particle* particles, int numParticles);
};

#endif

