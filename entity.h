//Final Project		entity.h	4/11/15		Author: Kurt Davis
//Renderable entity for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tile.h"
#include "LTexture.h"

typedef struct skills{
        int slashing;		//attack stat for sharp melee weapons
        int blunt;		//attack stat for blunt melee weapons
        int speed;		//stat to determine who attacks first
	int sneak;		//sneak attack skill buffs attack for first few hits
	int offmage;		//attack stat for magic
	int defmage;		//stat to determine what magic abilities are usable
} skill_type;

typedef struct stats{
	int type; 	//1 = warrior, 2 = rogue, 3 = mage	
	int level;
	int currentHealth;
	int maxHealth;
	int currentStamina;
	int maxStamina;
	int currentMana;
	int maxMana;
} stat_type;


class Entity{
	public:
		static const int DOT_WIDTH = 28;
		static const int DOT_HEIGHT = 35;
		static const int TILE_SIZE = 10;	//number of spaces charact moves
		Entity();			//default constructor
		~Entity();			//deconstructor
		virtual void render( SDL_Rect&, LTexture*) = 0;		//all entities must be renderable		
		virtual void toggleVisibility() = 0;	//all entities can change visibility
		virtual int isVisible() = 0;		//virtual get function for visibility

		int getVisibility();
		void setVisibility(int);

	private:
		int visibility;			//whether or not texture is rendered
};

#endif
