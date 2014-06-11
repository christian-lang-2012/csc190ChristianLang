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

void EnemyManager::update(float dt, Vector2& playerShipPosition)
{
	vector<Enemy*> deletedEnemies;

	for(vector<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++){
		Enemy* nextEnemy = *iter;
		bool isAlive = nextEnemy->update(dt, playerShipPosition);

		if (!isAlive){
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

void EnemyManager::checkIfShipIsHit(Vector2& bulletPosition, ParticleSystem& system)
{
	for(vector<Enemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++){
		Enemy* nextEnemy = *iter;
		Vector2 shipPosition = nextEnemy->getPosition();

		Vector2 d = shipPosition - bulletPosition;
		float length = d.Length();

		if(length <= 12)
		{
			nextEnemy->health--;
			ParticleEffect* explosion = new ExplosionEffect(0.10f, 0.01f, ColorChangeType::FIRE, shipPosition, 1.0f, 10.0f, 100);
			system.AddEffect(explosion);
		}
	}

}