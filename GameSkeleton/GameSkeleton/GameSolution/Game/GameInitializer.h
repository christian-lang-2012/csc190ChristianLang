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
#include "EnemyManager.h"
#include "Logger.h"
#include "Timer.h"

using Core::Input;

class GameInitializer
{
public:
	Spaceship mySpaceship;
	EnemySpaceship enemySpaceship;
	Boundary boundary;
	ParticleSystem system;
	EnemyManager enemySystem;
	Randomizer rando;
	float fps, spf;
	float constTimer, startTimer, deathTimer;
	int killCounter;

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
	bool UpdateIntro(float dt);
	bool UpdateInGame(float dt);
	bool UpdateDeath(float dt);
	void Draw(Core::Graphics& graphics);
	void DrawIntro(Core::Graphics& graphics);
	void DrawInGame(Core::Graphics& graphics);
	void DrawDeath(Core::Graphics& graphics);
	void Init();

};

#endif