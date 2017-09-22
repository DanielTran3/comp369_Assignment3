#pragma once

#include "sprite.h"
#include "toTheTopDefs.h"

#define MAX_ENEMIES 4800
#define PLATFORM_LENGTH 2
#define ENEMY "mappy/enemy.bmp"

class EnemyHandler {
	private:
		int _count;
		Sprite *_sprites[MAX_ENEMIES];
	
	public:
		EnemyHandler(void);
		~EnemyHandler(void);
		void AddEnemy(int spawningLevel, int xTile);
		int DrawEnemies(BITMAP *dest, int topOfScreen, int xOffset, int yOffset, Sprite *player);
		int GetPlatform(int level);
		void SpawnEnemies(void);
		void Create();
		Sprite *Get(int index);
		int Size();
};
