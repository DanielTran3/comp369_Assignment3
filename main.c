#include <allegro.h>
#include "toTheTop.h"

Sound *toTheTopSounds;
volatile int spikesY = BOTTOM;
volatile int timeElapsed = 0;
int gameoverFlag = 0;
/*
	Update the level that the spikes are at
*/
void update_deathSpikes(void) {
	spikesY -= mapblockheight;
	printf("UPDATING SPIKES: %i\n", spikesY);
}
END_OF_FUNCTION(update_deathSpikes)

/*
	Update the elapsed time
*/
void update_time(void) {
	timeElapsed++;
}
END_OF_FUNCTION(update_time);

/*
	Displays the player's current level and the time that has elapsed
*/
void displayGameInformation(Sprite *player, BITMAP *dest) {
	int xOffset = WIDTH / 2;
	int yOffset = 5;
	rectfill(dest, 0, 0, WIDTH, yOffset + 10, BLACK);
	textprintf_ex(dest, font, 10, yOffset, WHITE, 0, "Level Reached: %i       Spikes Level Reached: %i", 
				  player->getLevelReached(), mapheight - spikesY / mapblockheight);
	textprintf_ex(dest, font, WIDTH - 210, yOffset, WHITE, 0, "Time Elapsed: %i seconds", timeElapsed);
	hline(dest, 0, yOffset + 10, WIDTH, WHITE);
}

/*
	Displays the game over screen
*/
void displayGameOverScreen() {
//void displayGameOverScreen(PlayerInfo *player, FONT *gameOverFont) {
//	drawImage(GAMEOVER_BACKGROUND);
    int xOffset = WIDTH / 2;
    int yOffset = HEIGHT / 4 + 50;

    draw_pretty_box("Press Enter To Retry or ESC to Exit", xOffset / 2 + 20, yOffset, 30, 30, 14);
//    textprintf_centre_ex(screen, gameOverFont, xOffset, yOffset - 20, WHITE, -1, "Game Over");
    textprintf_centre_ex(screen, font, xOffset, yOffset - 20, WHITE, -1, "Game Over");
//	textprintf_centre_ex(screen, font, xOffset, yOffset + 5 * LINE_SPACING, WHITE, -1, "Your Score:    %i", player->getScore());
//    textprintf_centre_ex(screen, font, xOffset, yOffset + 6.5 * LINE_SPACING, WHITE, -1, "Highest Score: %i", player->getHighestScore());
//    textprintf_centre_ex(screen, font, xOffset, yOffset + 9 * LINE_SPACING, WHITE, -1, "Your Level:    %i", player->getLevel());
//    textprintf_centre_ex(screen, font, xOffset, yOffset + 10.5 * LINE_SPACING, WHITE, -1, "Highest Level: %i", player->getHighestLevel());
	textprintf_centre_ex(screen, font, xOffset, yOffset + 13 * LINE_SPACING, WHITE, -1, "Press Enter To Retry or ESC to Exit");
}

/*
	Get the number of characters in the inputted text
*/
int getHorizontalSpacing(const char *text) {
	return text_length(font, text) / CHARACTER_WIDTH;
}

/*
	Draw a box based on the text length and number of lines
*/
void draw_pretty_box(const char * textToMeasure, int x, int y, int offset_x, int offset_y, int numLines) {
	int textLength = getHorizontalSpacing(textToMeasure) * CHARACTER_WIDTH;
	rectfill(screen, x - offset_x, y - offset_y, x + textLength + offset_x, y + (numLines * LINE_SPACING) + offset_y, BLACK);
	rect(screen, x - offset_x, y - offset_y, x + textLength + offset_x, y + (numLines * LINE_SPACING) + offset_y, WHITE);
}

//tile grabber
BITMAP *grabframe(BITMAP *source, 
                  int width, int height, 
                  int startx, int starty, 
                  int columns, int frame)
{
    BITMAP *temp = create_bitmap(width,height);
    int x = startx + (frame % columns) * width;
    int y = starty + (frame / columns) * height;
    blit(source,temp,x,y,0,0,width,height);
    return temp;
}

int collided(int x, int y)
{
    BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}

void drawHLineOfSprites(Sprite *sprite, BITMAP *dest, int xDistance, int yLocation) {
	int tempY = yLocation;
	while (tempY < HEIGHT) {
		for (int x = 0; x < mapwidth; x++) {
			sprite->setX(x * mapblockwidth);
			sprite->setY(tempY);
			sprite->Draw(dest);
		}
		tempY += sprite->getHeight();
	}
}

/*
	Function to initialize the player's starting position and settings;
*/
void initializePlayer(Sprite *player) {
	player->Load("mappy/player.bmp");
	player->setX(WIDTH / 2);
	player->setY(BOTTOM - player->getHeight() - mapblockheight - 1);
	player->setWidth(32);
	player->setHeight(32);
	player->setAnimColumns(11);
	player->setCurFrame(8);
	player->setFrameDelay(10);
	player->setXDelay(1);
	player->setYDelay(5);
	player->setVelX(-3);
	player->setVelY(5);
}


int main(void) {
	int mapxoff, mapyoff;
	gameoverFlag = 0;
	allegro_init();	
	set_color_depth(24);
	install_keyboard();
	install_timer();
	srand(time(NULL));
	
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system!");
		return 1;
	}
	//toTheTopSounds = new Sound();
	
	int ret = set_gfx_mode(MODE_W, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting up the screen!");
		return 1;
	}
	
	// Create double buffer
	BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
	clear(buffer);
	
	MapLoad("mappy/toTheTop.fmp");
	
	// Update the spike's location every 3 seconds to move up a level
	LOCK_VARIABLE(spikesY);
    LOCK_FUNCTION(update_deathSpikes);
    install_int(update_deathSpikes, 3000);
    
    // Update the timer that the user is alive
	LOCK_VARIABLE(timeElapsed);
	LOCK_FUNCTION(update_time);
	install_int(update_time, 1000);
	
	Sprite *spike = new Sprite();
	ret = spike->Load(SPIKE_BMP);
	
	if (ret == 0) {
		allegro_message("Error loading mappy/deathSpike.bmp");
	}
	spike->setWidth(32);
	spike->setHeight(32);
	spike->setX(0);
	spike->setY(spikesY);
	
//	BITMAP *spikeOverlay = create_bitmap(WIDTH, BOTTOM);
//	clear_bitmap(spikeOverlay);
	
	Sprite *player = new Sprite();
	initializePlayer(player);

	SpriteHandler *enemySpriteHandler = new SpriteHandler();
	enemySpriteHandler->SpawnEnemies();
	//enemySpriteHandler->GetPlatform(1493);
	while(1) {
		player->UpdateLevelReached();
		player->PlayerControls();
		if (player->GetBlockData1(player->getX(), player->getY()) == 1) {
			gameoverFlag = 1;
		}
		//update the map scroll position
		mapxoff = WIDTH / 2;
		mapyoff = player->getY() - HEIGHT / 2;

        //avoid moving beyond the map edge
		if (mapxoff < 0) mapxoff = 0;
		if (mapxoff > (mapwidth * mapblockwidth - WIDTH))
            mapxoff = mapwidth * mapblockwidth - WIDTH;
		if (mapyoff < 0) 
            mapyoff = 0;
		if (mapyoff > (mapheight * mapblockheight - HEIGHT)) 
            mapyoff = mapheight * mapblockheight - HEIGHT;
        
//        printf("mapxoff: %i  mapyoff: %i\n", mapxoff, mapyoff);
		//draw the background tiles
		MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1);

        //draw foreground tiles
		MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1, 0);
		
		// If mapyoff + HEIGHT (Bottom of the screen) > spikesY, then the spikes should be
		// displayed on the screen.
		if (mapyoff + HEIGHT > spikesY) {
//			printf("SPIKES START: %i\n", spikesY - mapyoff);
//			printf("DIFF: %f\n", player->getY() - spikesY);
			// Display spikes from HEIGHT - (mapyoff + HEIGHT - spikesY) to the bottom of the screen
			drawHLineOfSprites(spike, buffer, WIDTH, spikesY - mapyoff);
		}
		
		// Draws Enemy and checks for player collision with enemy
		if (enemySpriteHandler->DrawEnemies(buffer, mapyoff, mapxoff, mapyoff, player)) {
			gameoverFlag = 1;
		}
		// Draw the player
		player->DrawFrame(buffer, mapxoff, mapyoff);
		displayGameInformation(player, buffer);
		vsync();
        acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
        release_screen();
		
		// Check if the bottom of the character has contacted the spikes
		if (player->getY() + player->getHeight() >= spikesY) {
			gameoverFlag = 1;
		}
		
		if (gameoverFlag) {
			// Ensure spikes are drawn, to show death from the spikes properly, since the spikes update
			// occur after spikes are drawn, but not draw the next level of spikes
			drawHLineOfSprites(spike, buffer, WIDTH, spikesY - mapyoff);
			blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
			displayGameOverScreen();
			while(!key[KEY_ESC]);
		}
		
		if (key[KEY_ESC]) {
			break;
		}
	}
	allegro_exit();
	return 1;
}
END_OF_MAIN();
