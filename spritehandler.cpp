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

/*
	Get collision with block
*/
int CollideWithBlock(int x, int y)
{
    BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
//	printf("Blockdata: %c\n", blockdata->tl);
//	printf("x: %i  y: %i\n", x, y);
	return blockdata->tl;
}

/*
	Gets a platform (defined as a specified number of foreground (collidable) tiles in a row)
	Returns a position where sprite can be placed ontop of, or -1 if no platform was founda the 
*/
int SpriteHandler::GetPlatform(int level) {
	int endingPlatformTile = 0;
	int tileCount = 0;
	
	for (int i = 1; i < mapwidth - 1; i++) {
		// Check collision with middle of the block

		if (CollideWithBlock(i * mapblockwidth, level * mapblockheight)) {
			// Keep track of a tile that the enemy can spawn ontop of;
			endingPlatformTile = i;
			// Increase the tile count
			if (++tileCount > PLATFORM_LENGTH) {
//				break;
			}
			printf("level: %i\n", level);
			printf("endingPlatformTile: %i\n", endingPlatformTile);
			printf("tileCount: %i\n", tileCount);
		}
		else {
			tileCount = 0;
		}
	}
	printf("return: %i\n", tileCount > PLATFORM_LENGTH ? endingPlatformTile : -1);
	return tileCount > PLATFORM_LENGTH ? endingPlatformTile : -1;
}

void SpriteHandler::SpawnEnemies() {
	// mapheight - 2 is the level above the starting ground level
	int spawningLevel = mapheight - 2;
	int randomLevel = 0;
	int platformEndingTile = 0;
	
	Sprite *enemy = new Sprite();
	enemy->Load(ENEMY);
	while (spawningLevel > TOP_LEVEL) {
		// Spawn an enemy every 10 levels
		//spawningLevel -= rand() % 10;
		
		// Only spawn an enemy where there are 3 or more tiles.
		// Don't spawn above level 0. This condition in the while is present for the case where
		// A level wasn't found and we try moving up more levels one at a time.
		while (spawningLevel > TOP_LEVEL) {
			platformEndingTile = GetPlatform(spawningLevel);

			// If no surface is found, then move up a level
			if (platformEndingTile == -1) {
				spawningLevel -= 1;
				continue;			
			}
			
			// Location has been found, break and move onto the next 10 levels			
			else {
				printf("FOUND\n");
				// Move spawningLevel up one to spawn enemy ontop of the level we found
				spawningLevel -= 1;
				// Spawn at the ending location
				// AddEnemy(spawningLevel, xTile);
				break;
			}
		}
	}	
}

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

