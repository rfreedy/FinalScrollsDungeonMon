//Final Project		fsdmlevel.h	4/11/15		Author: Kurt Davis
//Level Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef FSDMLEVEL_H
#define FSDMLEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Tile.h"
#include "LTexture.h"

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Tile constants
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites- Definitely needs to be changed for our sprite map
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

class FSDMLevel{
	public:
		FSDMLevel();
		~FSDMLevel();

		void free();

		void render( SDL_Rect&, LTexture*);

		bool constructed();

		bool setTiles();
	
		Tile** getTileSet();

		SDL_Rect* getTileClip(int);
	private:
		Tile* tileSet[ TOTAL_TILES ];

		bool construct_success;

		SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
};

#endif
