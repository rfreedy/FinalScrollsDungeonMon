//final project		character.h	3/3/15	Author: Kurt Davis

#ifndef CHARACTER_H
#define CHARACTER_H

#include<entity.h>
#include<stdio.h>
#include<SDL2/SDL.h>

class character: public entity{
	public:
		virtual void render();
		int getLevel();
		void levelUp();	
		void fight();		
	
	private:
		skill_type skills;
		stat_type stats;
};
