#ifndef SETUP_H
#define SETUP_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Tile.h"
#include "LTexture.h"

//Tile constants
const int TOTAL_TILE_SPRITES = 12;

class setUp {
public: 
	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia( Tile* tiles[] );

	//Frees media and shuts down SDL
	void close( Tile* tiles[] );

	//Box collision detector
	bool checkCollision( SDL_Rect a, SDL_Rect b );

	//Checks collision box against set of tiles
	bool touchesWall( SDL_Rect box, Tile* tiles[] );

	//Sets tiles from tile map
	bool setTiles( Tile *tiles[] );

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;
private: 
	//Scene textures
	LTexture gDotTexture;
	LTexture gTileTexture;
	SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
};

#endif 
