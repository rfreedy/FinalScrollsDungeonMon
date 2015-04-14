//Final Project		fsdmlevel.h	4/11/15		Author: Kurt Davis
//Level Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef FSDMLEVEL_H
#define FSDMLEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

class FSDMLevel{
	public:
		FSDMLevel();
		~FSDMLevel();

		void free();

		void render( SDL_Rect& );

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
