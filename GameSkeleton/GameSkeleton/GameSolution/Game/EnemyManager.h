#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Shape.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "ParticleSystem.h"
#include "ExplosionEffect.h"
#include <vector>

using std::vector;

class EnemyManager
{
private:
	vector<Enemy*> enemies;
public:
	void AddEnemy(Enemy* enemy);
	void RemoveEnemy(int index);

	void RemoveEnemy(Enemy* enemy);

	void update(float dt, Spaceship& playerShipPosition, ParticleSystem& system, int& killCount);
	void checkIfShipIsHit(Vector2& bulletPosition, ParticleSystem& system, int& killCount);
	void draw(Core::Graphics& graphics);
};

#endif