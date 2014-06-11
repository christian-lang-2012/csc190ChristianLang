#include "EnemyManager.h"

void EnemyManager::AddEnemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}

void EnemyManager::RemoveEnemy(int index)
{
	vector<Enemy*>::iterator removedEnemy = enemies.begin() + index;
	enemies.erase(removedEnemy);
}

void EnemyManager::RemoveEnemy(Enemy* enemy)
{
	bool found = false;

	unsigned int index = 0;
	vector<Enemy*>::iterator iter = enemies.begin(); 
	while(iter != enemies.end() && !found && (index < enemies.size())){
		if (enemy == *iter){
			iter = enemies.erase(iter);
			found = true;
		}
		else iter = enemies.begin() + index;

		index++;
	}
}

void EnemyManager::update(float dt, Spaceship& playerShip, ParticleSystem& system, int& killCount)
{
	vector<Enemy*> deletedEnemies;

	for(vector<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++){
		Enemy* nextEnemy = *iter;
		bool isAlive = nextEnemy->update(dt, playerShip.currentPosition);

		Vector2 d = playerShip.currentPosition - nextEnemy->getPosition();
		float length = d.Length();
		if(length <= 40)
		{
			playerShip.health--;
		}

		if (!isAlive){
			ParticleEffect* explosion = new ExplosionEffect(0.10f, 0.01f, ColorChangeType::EXPLOSION, nextEnemy->getPosition(), 1.0f, 10.0f, 100);
			system.AddEffect(explosion);
			killCount++;
			deletedEnemies.push_back(nextEnemy);
		}
	}

	for(vector<Enemy*>::iterator iter = deletedEnemies.begin();	iter != deletedEnemies.end(); iter++){
		Enemy* nextEnemy = *iter;
		RemoveEnemy(nextEnemy);
	}
}

void EnemyManager::draw(Core::Graphics& graphics)
{
	for(vector<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++){
		Enemy* nextEnemy = *iter;
		nextEnemy->draw(graphics);
	}
}

void EnemyManager::checkIfShipIsHit(Vector2& bulletPosition, ParticleSystem& system, int& killCount)
{
	for(vector<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++){
		Enemy* nextEnemy = *iter;
		Vector2 shipPosition = nextEnemy->getPosition();

		Vector2 d = shipPosition - bulletPosition;
		float length = d.Length();

		if(length <= 12)
		{
			nextEnemy->health--;
			ParticleEffect* explosion = new ExplosionEffect(0.10f, 0.01f, ColorChangeType::EXPLOSION, shipPosition, 1.0f, 10.0f, 100);
			system.AddEffect(explosion);
			killCount++;
		}
	}

}