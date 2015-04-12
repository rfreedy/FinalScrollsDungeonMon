//Final Project		character.h	4/11/15		Author: Kurt Davis
//Player Character for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "entity.h"

class Character: public Entity{
	public:
		Character();
		~Character();		

		virtual void render();
		void createCharacter();
		int getLevel();
		void levelUp();	
		void fight();		
	
	private:
		skill_type skills;
		stat_type stats;

		int level_coordinates_x;
		int level_coordinates_y;
		
		LTexture player_texture;
};

#endif
