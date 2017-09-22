#include "platform.h"

Platform::Platform() {
	_numPlatforms = 0;
}
Platform::~Platform() { }

/*
 Creates a platform at the specified location and can move in the x/y direction at the specified speed
*/
void Platform::CreatePlatform(int xLoc, int yLoc, double xSpeed, double ySpeed) {
	if (_numPlatforms < NUM_PLATFORMS) {
		_platforms[_numPlatforms] = new Sprite();
		_platforms[_numPlatforms]->Load(PLATFORM);
		_platforms[_numPlatforms]->setX(xLoc);
		_platforms[_numPlatforms]->setY(yLoc);
		_platforms[_numPlatforms]->setCurFrame(0);
		_platforms[_numPlatforms]->setAnimColumns(0);
		_platforms[_numPlatforms]->setFrameDelay(0);
		_platforms[_numPlatforms]->setTotalFrames(0);
		_platforms[_numPlatforms]->setXDelay(3);
		_platforms[_numPlatforms]->setYDelay(3);
		_platforms[_numPlatforms]->setVelX(xSpeed);
		_platforms[_numPlatforms]->setVelY(ySpeed);
		_numPlatforms++;
	}
}

/*
	Draws a platform if it is in the player's view and also checks with collision with the player
*/
int Platform::DrawPlatforms(BITMAP *dest, int topOfScreen, int xOffset, int yOffset, Sprite *player) {
	int collideWithPlayer = 0;
	for (int i = 0; i < _numPlatforms; i++) {
		if ((_platforms[i]->getY() > topOfScreen) && (_platforms[i]->getY() < (topOfScreen + HEIGHT))) {
			_platforms[i]->Move();
			printf("platform x: %f\n", _platforms[i]->getX());
			printf("platform y: %f\n", _platforms[i]->getY());
			
			// Check for player collision. Done in this function to reduce number of iterations over all enemies
			collideWithPlayer = player->Collided(_platforms[i], 0);
		}
	}
	return collideWithPlayer;
}

Sprite *Platform::GetPlatform(int index) {
	return _platforms[index];
}

int Platform::getNumPlatforms() {
	return _numPlatforms;
}
