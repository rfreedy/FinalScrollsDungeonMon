//Final Project		fsdmgame.h	4/11/15		Author: Kurt Davis
//Game Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef FSDMGAME_H
#define FSDMGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
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
	LTexture *gTileTexture = NULL;		//terrain sprite sheet
	LTexture *gDragonTexture = NULL;

	//For battle screen
	LTexture *battleBackground = NULL;
	
	LTexture *attackTextTexture = NULL;
	LTexture *abilityTextTexture = NULL;
	LTexture *escapeTextTexture = NULL;
	LTexture *optionTextTexture = NULL;

	LTexture *abil1TextTexture = NULL;
	LTexture *abil2TextTexture = NULL;
	LTexture *abil3TextTexture = NULL;
	LTexture *abil4TextTexture = NULL;

	LTexture *arrowTexture = NULL;
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
	
		void handleCombatEvent( SDL_Event& );

		//SDL_Rect gRedMan[8];		//class for aninamted character
	private:
		FSDMLevel *loaded_level = NULL;
		Texture_type textures;
		Character *player1 = NULL;
		Enemy *opponent = NULL;
		int gamestate;
		int current_level;
		int arrowState;
		int combat_menu_state;		//0: top level, 1: notification, 2: abilities
};

#endif
