#include "spritehandler.h"

SpriteHandler::SpriteHandler(void)
{
	_count = 0;
}

SpriteHandler::~SpriteHandler(void)
{
    //delete the sprites
	for (int n = 0; n < _count; n++)
		delete _sprites[n];
}

/*
	Add a sprite to the sprite handler
*/
void SpriteHandler::AddEnemy(int spawningLevel, int xTile) 
{
//	if (spr != NULL) {
//		_sprites[_count] = spr;
//		_count++;
//	}
}

void SpriteHandler::SpawnEnemies(void) {
	printf("total levels: %i\n", mapheight);
	printf("total width: %i\n", mapwidth);
	// mapheight - 2 is the level above the starting ground level
	int spawningLevel = mapheight - 2;
	int randomLevel = 0;
	int tileCount = 0;
	int endingPlatformTile = 0;
	Sprite *enemy = new Sprite();
	enemy->Load(ENEMY);
	printf("---spawningLevel: %i\n", spawningLevel);
	endingPlatformTile = 0;
	// Start from 1 and end at mapwidth - 1 to exclude the border tiles
	for (int i = 1; i < mapwidth - 1; i++) {
		// Check collision with middle of the block
		if (enemy->CollideWithBlock(i * mapblockwidth / 2, spawningLevel * mapblockheight - (mapblockheight / 2))) {
			// Keep track of a tile that the enemy can spawn ontop of;
			endingPlatformTile = i;
			// Increase the tile count
			if (++tileCount > 2) {
//					break;
			}
			printf("level: %i\n", spawningLevel);
			printf("endingPlatformTile: %i\n", endingPlatformTile);
			printf("tileCount: %i\n", tileCount);
		}
		else {
			tileCount = 0;
		}
		// Location has been found, break and move onto the next 10 levels
//		if (tileCount > 2) {
//			printf("FINAL spawningLevel: %i\n", spawningLevel);
//			printf("FINAL endingPlatformTile: %i\n", endingPlatformTile);
//			printf("FINAL tileCount: %i\n", tileCount);
//			// Move spawningLevel up one to spawn enemy ontop of the level we found
//			spawningLevel -= 1;
//			// Spawn at the ending location
//			// AddEnemy(spawningLevel, xTile);
//			break;
//		}
//		// If no surface is found, then move up a level
//		else {
//			spawningLevel -= 1;
//			continue;
//		}
	}
}

//void SpriteHandler::SpawnEnemies() {
//	int spawningLevel = mapheight;
//	int randomLevel = 0;
//	int tileCount = 0;
//	int endingPlatformTile = 0;
//	Sprite *enemy = new Sprite();
//	enemy->Load(ENEMY);
//	while (spawningLevel > TOP_LEVEL) {
//		// Spawn an enemy every 10 levels
//		spawningLevel -= rand() % 10;
//		
//		// Only spawn an enemy where there are 3 or more tiles.
//		// Don't spawn above level 0. This condition in the while is present for the case where
//		// A level wasn't found and we try moving up more levels one at a time.
//		while (spawningLevel > TOP_LEVEL) {
//			for (int i = 0; i < mapwidth; i++) {
//				if (enemy->CollideWithBlock(i * mapblockwidth / 2, spawningLevel * mapblockheight)) {
//					// Keep track of a tile that the enemy can spawn ontop of;
//					endingPlatformTile = i;
//					// Increase the tile count
//					tileCount++;
//				}
//				else {
//					tileCount = 0;
//				}
//			}
//			// Location has been found, break and move onto the next 10 levels
//			if (tileCount > 2) {
//				// Move spawningLevel up one to spawn enemy ontop of the level we found
//				spawningLevel -= 1;
//				// Spawn at the ending location
//				// AddEnemy(spawningLevel, xTile);
//				break;
//			}
//			// If no surface is found, then move up a level
//			else {
//				spawningLevel -= 1;
//				continue;
//			}
//		}
//	}	
//}

/*
	Create a sprite
*/
void SpriteHandler::Create() 
{
	_sprites[_count] = new Sprite();
	_count++;
}

/*
	Retrieve a sprite
*/
Sprite *SpriteHandler::Get(int index)
{
	return _sprites[index];
}

/*
	Get the number of sprites in the sprite handler
*/
int SpriteHandler::Size() {
	return _count;
}

