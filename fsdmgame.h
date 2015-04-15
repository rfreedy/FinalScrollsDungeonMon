//Final Project		fsdmgame.h	4/11/15		Author: Kurt Davis
//Game Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef FSDMGAME_H
#define FSDMGAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>


class FSDMGame{
	public:
		FSDMGame();
		~FSDMGame();
		void play();

		bool init();
		void close();
	private:
		FSDMLevel *loaded_level = NULL;
		int current_level;

		FSDMCharacter *player1 = NULL;
		
		SDL_Renderer *gRenderer = NULL;
};

#endif