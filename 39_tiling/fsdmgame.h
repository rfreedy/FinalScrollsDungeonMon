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
#include "fsdmgame.cpp"
#include "Tile.h"
#include "LTexture.h"

typedef struct Textures {
	LTexture *gDotTexture = NULL;
	LTexture *gTileTexture = NULL;
} Texture_type;

class FSDMGame{
	public:
		FSDMGame();
		~FSDMGame();

		void start();
		bool init();
		void close();
		bool loadMedia( Tile* tiles[] );
	private:
		FSDMLevel *loaded_level = NULL;
		int current_level;
		Texture_type textures;
		FSDMCharacter *player1 = NULL;

		SDL_Renderer *gRenderer = NULL;
	
		SDL_Window* gWindow = NULL;

}

#endif
