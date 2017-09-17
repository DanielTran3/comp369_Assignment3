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
	player->Load("player.bmp");
	player->setX(50);
	player->setY(BOTTOM - player->getHeight() - 50);
}

/*
	Function to initialize the frames for sprites
*/
void loadSpriteAnimations() {
	BITMAP *temp;
	temp = load_bitmap("guy.bmp", NULL);
    for (int n = 0; n < 8; n++)
    {
    	player_image[n] = grabframe(temp, 32, 32, 0, 0, 11, n);	
	}
    destroy_bitmap(temp);
}

int main(void) {
	int mapxoff, mapyoff;
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
		mapxoff = player->getX() + player->getWidth()/2 - WIDTH/2 + 10;
		mapyoff = player->getY() + player->getHeight()/2 - HEIGHT/2 + 10;


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
		if (key[KEY_ESC]) {
			break;
		}
	}
	allegro_exit();
	return 1;
}
END_OF_MAIN();
