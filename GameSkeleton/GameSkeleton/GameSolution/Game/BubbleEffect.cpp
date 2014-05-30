#include "BubbleEffect.h"

void BubbleEffect::Draw_MidpointCircle(Core::Graphics& graphics, float radius, Vector2 position)
{
	float PI = 3.14159265f;
	float radiansPerInc = 1.0f / radius; //(2 * Utils::PI) / circumference;
	float angle = 0.0f;

	do{
		Vector2 translation = rn.RandomUnitVector() * radius;
		Vector2 pixelPos = position + translation;
		graphics.DrawLine(pixelPos.X - 1, pixelPos.Y, (pixelPos.X + 1), pixelPos.Y);
		graphics.DrawLine(pixelPos.X, pixelPos.Y - 1, pixelPos.X , pixelPos.Y + 1);

		angle += radiansPerInc;
	}while(angle < (2.0f * PI));
}

void BubbleEffect::draw(Core::Graphics& g)
{
	for (int i = 0; i < numOfParticles; i++){
		if (particles[i].isAlive()){
			g.SetColor(particles[i].currentColor);
			Draw_MidpointCircle(g, particles[i].radius, particles[i].position);
			g.SetColor(RGB(255,255,255));
		}
	}
}

bool BubbleEffect::update(bool isThrusting1, float angle1, Vector2 pos1, float dt)
{
	isThrusting = isThrusting1;
	angle = angle1;
	position = pos1;

	return update(dt);
}

bool BubbleEffect::update(float dt)
{
	for (int i = 0; i < numOfParticles; i++){
		particles[i].update(dt);

		if (particles[i].isAlive()){
			float totalDeccel = deccel + rn.GuassianFunc(particles[i].age, (particles[i].lifetime / 2), 0.5f, 0.0f, particles[i].age);

			float oldLength = particles[i].velocity.Length();
			float newLength = oldLength - totalDeccel;
			float scalar = newLength / oldLength;

			Vector2 newVelocity = scalar * particles[i].velocity;
			particles[i].velocity = (newVelocity.Length() > 1) ? newVelocity : Vector2(0.0f, 0.0f);

			particles[i].position = particles[i].position + newVelocity;
		}
		else if (isThrusting){
			Vector2 velocity = rn.RandomInRange(minVelocity, maxVelocity) * rn.RandomUnitVector(angle, variance);
			float LIFETIME = rn.RandomInRange(MIN_LIFETIME, MAX_LIFETIME);

			particles[i] = Particle(position, velocity, LIFETIME, colorChange);
			particles[i].radius = rn.RandomInRange(minRadius, maxRadius);
		}
	}

	return true;
}