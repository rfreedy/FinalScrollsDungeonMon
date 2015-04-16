//Dot.h Practice for the final project

#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Tile.h"
#include "LTexture.h"


class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 40;
		static const int DOT_HEIGHT = 40;
		static const int TILE_SIZE = 40;	//number of spaces charact moves

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 5;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[] );

		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		//Shows the dot on the screen
		void render( SDL_Rect&, LTexture*);

		bool touchesWall( SDL_Rect, Tile* [] );

		bool checkCollision( SDL_Rect, SDL_Rect);

		//friend class FSDMGame;

    private:
		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		int mVelX, mVelY;

		SDL_Rect* currentClip;	//change
		int count;		//need count
		int up, down, right, left;
};

#endif
