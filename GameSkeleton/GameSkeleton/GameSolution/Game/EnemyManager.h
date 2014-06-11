#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Shape.h"
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

	void update(float dt, Vector2& playerShipPosition);
	void checkIfShipIsHit(Vector2& bulletPosition, ParticleSystem& system);
	void draw(Core::Graphics& graphics);
};

#endif