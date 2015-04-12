//Final Project		enemy.h	4/11/15		Author: Kurt Davis
//Enemy Character for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

class Enemy: public Entity{
	public:
		Enemy();	//constructor
		~Enemy();	//deconstructor
		virtual void render();	//implementation of pure virtual
	private:
		stat_type stats;	//creates structure for stats (health, mana,stamina)
		skill_type skills;	//structure for skills (atk, def, power)
		
};

#endif
