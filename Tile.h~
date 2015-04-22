//Tile.h Final Project

#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "LTexture.h"

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

class Tile
{
    public:
		//Initializes position and type
		Tile( int x, int y, int tileType );

		//Shows the tile
		void render( SDL_Rect&, SDL_Rect*, LTexture*);

		//Get the tile type
		int getType();

		//Get the collision box
		SDL_Rect getBox();
	
		bool checkCollision( SDL_Rect, SDL_Rect);

    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;
};

#endif
