#include "Randomizer.h"

float Randomizer::RandomFloat()
{
	return (float) rand() / RAND_MAX;
}

const float TWO_PI = 2*3.1415926f;
Vector2 Randomizer::RandomUnitVector()
{
	float angle = TWO_PI * RandomFloat();
	return Vector2(cos(angle), sin(angle));
}

float Randomizer::RandomInRange(float min, float max)
{
	return RandomFloat() * (max - min +1) + min;
}

float Randomizer::GuassianFunc(float curveHeight, float peakPos, float steepness, float asym, float x)
{
	float powerNumerator = pow((x - peakPos), 2);
	float powerDenominator = 2 * (steepness * steepness);
	float power = -(powerNumerator / powerDenominator);

	return (curveHeight * pow(E, power)) + asym;
}

Vector2 Randomizer::RandomUnitVector(float angle, float variance)
{
	float variedAngle = (RandomInRange((angle - variance), (angle + variance))) - 0.5f;
	Vector2 result = Vector2(sin(variedAngle), cos(variedAngle));
	return result;
}

Vector2 Randomizer::RandomVelocity(float min, float max)
{
	float angle = (2 * PI) * RandomFloat();
	Vector2 result = Vector2(cos(angle), sin(angle)) * RandomInRange(min, max);
	return result;
}


