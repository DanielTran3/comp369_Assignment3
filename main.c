#include <allegro.h>
#include "toTheTop.h"

Sound *toTheTopSounds;
BITMAP *player_image[11];

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

/*
	Function to initialize the player's starting position and settings;
*/
void initializePlayer(Sprite *player) {
	player->Load("mappy/player.bmp");
	player->setX(WIDTH / 2);
	player->setY(HEIGHT - player->getHeight() - 32);
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

/*
	Function to initialize the frames for sprites
*/
void loadSpriteAnimations() {
	BITMAP *temp;
	temp = load_bitmap("mappy/player.bmp", NULL);
    for (int n = 0; n < 11; n++)
    {
    	player_image[n] = grabframe(temp, 32, 32, 0, 0, 11, n);	
	}
    destroy_bitmap(temp);
}

int main(void) {
	int mapxoff, mapyoff, facing;
	allegro_init();	
	set_color_depth(24);
	install_keyboard();
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
	
	Sprite *player = new Sprite();
	initializePlayer(player);
	loadSpriteAnimations();
	
	while(1) {
		//update the map scroll position
		mapxoff = WIDTH / 2;
		mapyoff = BOTTOM;

        //avoid moving beyond the map edge
		if (mapxoff < 0) mapxoff = 0;
		if (mapxoff > (mapwidth * mapblockwidth - WIDTH))
            mapxoff = mapwidth * mapblockwidth - WIDTH;
		if (mapyoff < 0) 
            mapyoff = 0;
		if (mapyoff > (mapheight * mapblockheight - HEIGHT)) 
            mapyoff = mapheight * mapblockheight - HEIGHT;
		//draw the background tiles
		MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1);

        //draw foreground tiles
		MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, WIDTH-1, HEIGHT-1, 0);
		
		player->PlayerControls();
		// Draw the player
		player->DrawFrame(buffer);
//		draw_sprite(buffer, player_image[8], 
//                player->getX(), player->getY());
		//blit the double buffer 
		vsync();
        acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, WIDTH-1, HEIGHT-1);
        release_screen();
		if (key[KEY_ESC]) {
			break;
		}
	}
	allegro_exit();
	return 1;
}
END_OF_MAIN();
