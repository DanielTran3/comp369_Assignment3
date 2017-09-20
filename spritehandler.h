#pragma once

#include "sprite.h"
#define MAX_ENEMIES 4800
#define TOP_LEVEL 0
#define ENEMY "mappy/enemy.bmp"

class SpriteHandler {
	private:
		int _count;
		Sprite *_sprites[MAX_ENEMIES];
	
	public:
		SpriteHandler(void);
		~SpriteHandler(void);
		void AddEnemy(int spawningLevel, int xTile);
		void SpawnEnemies(void);
		void Create();
		Sprite *Get(int index);
		int Size();
};
