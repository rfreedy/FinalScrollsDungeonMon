//Final Project		main.cpp	4/11/15		Author: Kurt Davis
//Driver for FSDM game
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "fsdmgame.h"
#include "fsdmlevel.h"
#include "Dot.h"
#include "Tile.h"
#include "LTexture.h"

int main(){
	printf("start");
	FSDMGame game1;

	game1.start();	

	return 0;
}
