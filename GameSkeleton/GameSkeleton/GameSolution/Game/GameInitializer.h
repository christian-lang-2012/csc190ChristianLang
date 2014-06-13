#ifndef GAME_INITIALIZER_H
#define GAME_INITIALIZER_H
#include "Spaceship.h"
#include "EnemySpaceship.h"
#include "ParticleSystem.h"
#include "Randomizer.h"
#include "EnemyManager.h"
#include "RecursiveShape.h"
#include "BubbleEffect.h"
#include "DebugMemory.h"

using Core::Input;

class GameInitializer
{
public:
	ParticleSystem system;
	EnemyManager enemySystem;
	Bullet globalBullets[100];
	Spaceship mySpaceship;
	EnemySpaceship enemySpaceship;
	Boundary boundary;
	RecursiveShape rs;
	Randomizer rando;
	int killCounter, SCREEN_WIDTH, SCREEN_HEIGHT, boudnaryTypeStuff, bulletCounter;
	float width, height, fps, spf, constTimer, startTimer, deathTimer;
	unsigned int counts, sizes, highwater;
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