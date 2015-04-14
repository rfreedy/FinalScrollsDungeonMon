//Final Project		enemy.cpp	4/11/15		Author: Kurt Davis
//Enemy Character for FSDM game, implementation file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <stdio.h>
#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.h"
#include "character.h"

//default constructor
Enemy::Enemy(): Entity(){

	//initialize values in skills/stats structs	
	skills.slashing = 10;
	skills.blunt = 10;
	skills.speed = 10;
	skills.sneak = 10;
	skills.offmage = 10;
	skills.defmage = 10;

	stats.type = 0;
	stats.level = 1;
	stats.currentHealth = 100;
	stats.maxHealth = 100;
	stats.currentStamina = 100;
	stats.maxStamina = 100;
	stats.currentMana = 100;
	stats.maxMana = 100;

	//initialize coordinates to impossible position, indicator of uninitialized level
	level_coordinates_x = -2;
	level_coordinates_y = -2;

	//TODO: init unit_texture
}

//deconstructor
Enemy::~Enemy(){
	//TODO: free/delete unit_texture
}

//virtual render function, common to entities
void Enemy::render(){
	//TODO: draw unit_texture to screen at coordinates
}

void Enemy::toggleVisibility(){
	setVisibility(!getVisibility());
}

int Enemy::isVisible(){
	return getVisibility();
}

int Enemy::getCurrentHealth(){
	return stats.currentHealth;
}

int Enemy::getCurrentStamina(){
	return stats.currentStamina;
}

int Enemy::getCurrentMana(){
	return stats.currentMana;
}

void Enemy::defend(){
	//TODO: take damage function	
	return;
}

void Enemy::attack(){
	//TODO: calculate damage
	return;
}
