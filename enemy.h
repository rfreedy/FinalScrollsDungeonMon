//Final Project		enemy.h	4/11/15		Author: Kurt Davis
//Enemy Character for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.h"
#include "character.h"

class Enemy: public Entity{
	public:
		Enemy();	//constructor
		~Enemy();	//deconstructor

		virtual void render();	//implementation of pure virtual
		virtual void toggleVisibility();
		virtual int isVisible();

		int getCurrentHealth();
		int getCurrentStamina();
		int getCurrentMana();

		int speedCheck();

		void refilStamina();

		void defend(int);	//take damage
		int attack();		//calculate output damage
	private:
		int getBestAttack(int);	//returns type of best attack; 1=slash, 2=blunt, 3=magic

		stat_type stats;	//creates structure for stats (health, mana,stamina)
		skill_type skills;	//structure for skills (atk, def, power)

		int level_coordinates_x;
		int level_coordinates_y;
		
		//LTexture unit_texture;		
};

#endif
