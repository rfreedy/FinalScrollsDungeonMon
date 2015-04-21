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
#include "winrend.h"
#include "Tile.h"
#include "LTexture.h"

class Character: public Entity{
	public:/*
		static const int DOT_WIDTH = 40;	//height and width
		static const int DOT_HEIGHT = 40;
		static const int TILE_SIZE = 40;	//number of spaces charact moves*/
		static const int DOT_VEL = 20;

		Character();
		~Character();		

		virtual void render( SDL_Rect&, LTexture*);
		virtual void toggleVisibility();
		virtual int isVisible();

		void createCharacter();
		int getLevel();
		void levelUp();	
		void fight(Enemy&);		

		int getCurrentHealth();
		int getCurrentStamina();
		int getCurrentMana();

		int getMaxHealth();
		int getMaxStamina();
		int getMaxMana();
	
		int speedCheck();


		void replenish();
		void refillStamina();
		void refillMana();

		void defend(int);		//take damage
		int attack(int);		//calculate output damage

		//movement, animation, and tiling
		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );
		//Moves the dot and check collision against tiles
		int  move( Tile *tiles[] );
		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );
		//Shows the dot on the screen
		//void render( SDL_Rect&, LTexture*);
		int touchesWall( SDL_Rect, Tile* [] );
		bool checkCollision( SDL_Rect, SDL_Rect);
	
	private:
		int getBestAttack();
		
		//helper functions
		void incStats(int);
		void incSkills(int);		

		skill_type skills;
		stat_type stats;

		int level_coordinates_x;
		int level_coordinates_y;
		
		//movement, animation and tiling
		SDL_Rect mBox;	//Collision box of the dot
		//The velocity of the dot
		int mVelX, mVelY;
		SDL_Rect* currentClip;	
		int count;
		int up, down, right, left;
};

#endif
