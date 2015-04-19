//Final Project		character.cpp	4/11/15		Author: Kurt Davis
//Player Character for FSDM game, implementation file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <stdio.h>
#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"

//default constructor
Entity::Entity(){
	visibility = 1;
}

//deconstructor
Entity::~Entity(){
	//nothing so far; no pointers
}

//get function for visibility
int Entity::getVisibility(){
	return visibility;
}

//set function for visibility
void Entity::setVisibility(int v){
	visibility = v;
}
