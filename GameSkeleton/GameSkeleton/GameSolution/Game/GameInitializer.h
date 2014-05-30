#ifndef GAME_INITIALIZER_H
#define GAME_INITIALIZER_H
#include "Engine.h"
#include "ExplosionEffect.h"
#include "BubbleEffect.h"
#include "ParticleSystem.h"
#include "Spaceship.h"
#include "Core.h"
#include "EnemySpaceship.h"
#include "RecursiveShape.h"

using Core::Input;

class GameInitializer
{
public:
	Spaceship mySpaceship;
	EnemySpaceship enemySpaceship;
	Boundary boundary;
	ParticleSystem system;

	Bullet globalBullets[100];

	RecursiveShape rs;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	float width;
	float height;
	int boudnaryTypeStuff;
	int bulletCounter;
	bool isPress;

	GameInitializer(void);
	~GameInitializer(void);
	bool Update(float dt);
	void Draw(Core::Graphics& graphics);
	void Init();

};

#endif