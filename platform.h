#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "sprite.h"

#define NUM_PLATFORMS 20
#define PLATFORM "mappy/moving_platform.bmp"
#define START_PLATFORM_HEIGHT 1345

class Platform {
	private:
		int _numPlatforms;
		Sprite *_platforms[NUM_PLATFORMS];
	public:
		Platform();
		~Platform();
		
		void CreatePlatform(int xLoc, int yLoc, double xSpeed, double ySpeed);
		int DrawPlatforms(BITMAP *dest, int topOfScreen, int xOffset, int yOffset, Sprite *player);
		Sprite *GetPlatform(int index);
				
		int getNumPlatforms();
};

#endif
