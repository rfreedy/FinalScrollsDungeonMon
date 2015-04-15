//Final Project		fsdmlevel.h	4/11/15		Author: Kurt Davis
//Level Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef FSDMLEVEL_H
#define FSDMLEVEL_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

class FSDMLevel{
	public:
		FSDMLevel();
		~FSDMLevel();

		
	private:
		LTexture floor_texture;
};

#endif