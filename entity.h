//final project		entity.h	3/3/15	Author: Kurt Davis

#ifndef ENTITY_H
#define ENTITY_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

typedef struct skills{
        int melee;
        int range;
        int magic;
} skill_type;

typedef struct stats{
	int level;
	int health;
	int stamina;
	int mana;
} stat_type;


class entity{
	public:
		entity();
		~entity();
		virtual void render() = 0;	//all entities must be renderable		

	private:
		int isVisible;
		SDL_Surface* texture;
};
