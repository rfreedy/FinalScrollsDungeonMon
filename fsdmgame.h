//Final Project		fsdmgame.h	4/11/15		Author: Kurt Davis
//Game Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef FSDMGAME_H
#define FSDMGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "LTexture.h"
#include "Tile.h"
#include "Dot.h"
#include "fsdmlevel.h"
#include "entity.h"
#include "character.h"
#include "enemy.h"


typedef struct Textures {
	LTexture *gDotTexture = NULL;
	LTexture *gTileTexture = NULL;
	LTexture *battleBackground = NULL;
} Texture_type;


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class FSDMGame{
	public:
		//FSDMGame();
		//~FSDMGame();

		void start();
		int play();
		bool init();
		void close();
		bool loadMedia();
		//SDL_Rect gRedMan[8];		//class for aninamted character
	private:
		FSDMLevel *loaded_level = NULL;
		int current_level;
		Texture_type textures;
		Character *player1 = NULL;
	
};

#endif
