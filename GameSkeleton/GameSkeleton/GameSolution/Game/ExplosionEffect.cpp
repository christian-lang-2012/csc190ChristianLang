#include "ExplosionEffect.h"

void ExplosionEffect ::draw(Core::Graphics& g)
{
	for (int i = 0; i < numOfParticles; i++){
			if (particles[i].isAlive()){
				g.SetColor(particles[i].currentColor);

				float x = particles[i].position.X;
				float y = particles[i].position.Y;
				g.DrawLine(x, y, (x + 3), y);
				g.SetColor(RGB(255,255,255));
			}
		}
}

bool ExplosionEffect::update(bool isThrusting, float angle, Vector2 pos, float dt)
{
		isThrusting;
		angle;
		pos;

		return update(dt);
}

bool ExplosionEffect::update(float dt)
{
	bool isAlive = false;

	for (int i = 0; i < numOfParticles; i++){
			particles[i].update(dt);

			if (particles[i].isAlive()){
				isAlive = true;

				float totalDeccel = deccel + rn.GuassianFunc(particles[i].age, 
					(particles[i].lifetime / 2), 0.5f, 0.0f, particles[i].age);

				float oldLength = particles[i].velocity.Length();
				float newLength = oldLength - totalDeccel;
				float scalar = newLength / oldLength;

				Vector2 newVelocity = scalar * particles[i].velocity;
				particles[i].velocity = (newVelocity.Length() > MIN_VEL) ? newVelocity : Vector2(0.0f, 0.0f);

				particles[i].position = particles[i].position + newVelocity;
			}
		}

		return isAlive;
}