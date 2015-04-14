//Final Project		character.h	4/11/15		Author: Kurt Davis
//Player Character for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.h"
#include "enemy.h"

class Character: public Entity{
	public:
		Character();
		~Character();		

		virtual void render();
		virtual void toggleVisibility();
		virtual int isVisible();

		void createCharacter();
		int getLevel();
		void levelUp();	
		void fight(Enemy&);		

		void defend(int);		//take damage
		int attack(int);		//calculate output damage
	
	private:
		int getBestAttack();
		
		//helper functions
		void incStats(int);
		void incSkills(int);		

		skill_type skills;
		stat_type stats;

		int level_coordinates_x;
		int level_coordinates_y;
		
		//LTexture player_texture;
};

#endif
