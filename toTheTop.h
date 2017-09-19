#ifndef _TOTHETOP_H
#define _TOTHETOP_H

#include <allegro.h>
#include "sprite.h"
#include "sound.h"

#define MODE_W GFX_AUTODETECT_WINDOWED
#define MODE_F GFX_AUTODETECT_FULLSCREEN

#define WIDTH 640
#define HEIGHT 480
#define BOTTOM 48000 - HEIGHT

#define CHARACTER_WIDTH 8
#define LINE_SPACING 10

#define HELP_SCREEN "images/help.bmp"
#define TITLE_BACKGROUND "images/title.pcx"
#define INSTRUCTIONS_BACKGROUND "images/instructions.pcx"
#define LEVELS_BACKGROUND "images/levels.pcx"
#define BACKGROUND "images/background_1.pcx"
#define GAMEOVER_BACKGROUND "images/ending.pcx"

#define SPIKE_BMP "mappy/deathSpike.bmp"

#define WHITE makecol(255, 255, 255)
#define BLACK makecol(0, 0, 0)
#define LIGHT_GREEN makecol(100, 255, 0)
#define RED makecol(255, 0, 0)

#endif
