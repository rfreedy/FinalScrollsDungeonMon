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
const int LEVEL_WIDTH = 1632;
const int LEVEL_HEIGHT = 1248;

const int TOTAL_TILES = 1989;
const int TOTAL_TILE_SPRITES = 19;

//The different tile sprites- Definitely needs to be changed for our sprite map
//The different tile sprites
const int TILE_GRASS = 0;
const int TILE_DIRT = 1;
const int TILE_DUNGEON = 2;
const int TILE_SKINNYTREES = 3;
const int TILE_LAVA = 4;
const int TILE_SANDWALL = 5;
const int TILE_WATERFALL = 6;
const int TILE_BOULDERS = 7;
const int TILE_BRICKS = 8;
const int TILE_MOUNTAINS = 9;
const int TILE_TREES = 10;
const int TILE_WATER = 11;
const int TILE_SNOW_TREES = 12;
const int TILE_SNOW_MOUNTAINS = 13;
const int TILE_SNOW = 14;
const int TILE_STAIR_1 = 15;
const int TILE_BRICKS_WALKING = 16;
const int TILE_LAVA_BRIDGE = 17;
const int TILE_STAIR_UP = 18;

//declare dungeon map constants
const int OVERWORLD = 2; 
const int DUNGEON1 = 3;
const int DUNGEON2 = 4;

class FSDMLevel{
	public:
		FSDMLevel(int = OVERWORLD);
		~FSDMLevel();

		void free();

		void render( SDL_Rect&, LTexture*);

		bool constructed();

		bool setTiles(int);
	
		Tile** getTileSet();

		SDL_Rect* getTileClip(int);
	private:
		Tile* tileSet[ TOTAL_TILES ];

		bool construct_success;

		SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
};

#endif
