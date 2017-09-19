#include <allegro.h>
#include "toTheTop.h"

Sound *toTheTopSounds;
volatile int spikesY = BOTTOM + HEIGHT;

void draw_deathSpikes(void) {
	spikesY -= mapblockheight;
	printf("UPDATING SPIKES: %i\n", spikesY);
}
END_OF_FUNCTION(draw_deathSpikes)

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
	for (int x = 0; x < xDistance; x += sprite->getWidth()) {
		blit(sprite->getImage(), dest, 0, 0, x, yLocation, sprite->getWidth(), sprite->getHeight());
	}
}

/*
	Function to initialize the player's starting position and settings;
*/
void initializePlayer(Sprite *player) {
	player->Load("mappy/player.bmp");
	player->setX(WIDTH / 2);
	player->setY(BOTTOM + HEIGHT - player->getHeight() - mapblockheight - 1);
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
//void loadSpriteAnimations() {
//	BITMAP *temp;
//	temp = load_bitmap("mappy/player.bmp", NULL);
//    for (int n = 0; n < 11; n++)
//    {
//    	player_image[n] = grabframe(temp, 32, 32, 0, 0, 11, n);	
//	}
//    destroy_bitmap(temp);
//}

int main(void) {
	int mapxoff, mapyoff;
	
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
	
	LOCK_VARIABLE(spikesY);
    LOCK_FUNCTION(draw_deathSpikes);
    install_int(draw_deathSpikes, 5000);
	Sprite *spike = new Sprite();
	ret = spike->Load(SPIKE_BMP);
	if (ret == 0) {
		allegro_message("Error loading mappy/deathSpike.bmp");
	}
	spike->setWidth(32);
	spike->setHeight(32);
	spike->setX(0);
	spike->setY(spikesY);
	
	BITMAP *spikeOverlay = create_bitmap(WIDTH, BOTTOM + HEIGHT);
	clear_bitmap(spikeOverlay);
	
	Sprite *player = new Sprite();
	initializePlayer(player);
//	loadSpriteAnimations();
	
	while(1) {
		player->PlayerControls();
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
		
		// Draw the player
		player->DrawFrame(buffer, mapxoff, mapyoff);
//		draw_sprite(buffer, player_image[8], 
//                player->getX(), player->getY());
		//blit the double buffer 
		if (spike->getY() != spikesY) {
			printf("y Pos: %f\n", player->getY());
			printf("spike x Pos: %f\n", spike->getX());
			printf("spike y Pos: %f\n", spike->getY());
			printf("spike width: %f\n", spike->getWidth());
			printf("spike height: %f\n", spike->getHeight());
			spike->setY(spikesY);
//			drawHLineOfSprites(spike, buffer, WIDTH, spikesY);
//			while (spike->getX() < WIDTH) {
//				printf("x Pos: %f\n", spike->getX());				
////				blit(spike->getImage(), buffer, 0, 0, spike->getX(), spike->getY(), spike->getWidth(), spike->getHeight());
//				drawSprite(buffer, spike->getImage(), 0, BOTTOM + HEIGHT - 32);
////				blit(spike->getImage(), buffer, 0, 0, spike->getX(), BOTTOM + HEIGHT - 32, 32, 32);
//				spike->setX(spike->getX() + spike->getWidth());
//			}
//			spike->setX(0);
			draw_sprite(spikeOverlay, spike->getImage(), WIDTH / 2, HEIGHT / 2);
		}
		blit(spikeOverlay, buffer, 0, mapyoff + HEIGHT / 2, 0, 0, WIDTH, HEIGHT);
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
