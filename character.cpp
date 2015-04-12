//Final Project		character.cpp	4/11/15		Author: Kurt Davis
//Player Character for FSDM game, implementation file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "character.h"

//default constructor
Character::Character(): Entity(){

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
	level_coordinates_x = -1;
	level_coordinates_y = -1;

	//TODO: init player_texture
}

//deconstructor
Character::~Character(){
	//TODO: free/delete player_texture
}

//virtual render function, common to entities
void Character::render(){
	//TODO: draw player_texture to screen
}

//interactive character creation
void Character::createCharacter(){
	//TODO: convert to screen and GUI
	
	/*********text based version*********/
	
	//select class
	printf("Enter character class: (1) Warrior, (2) Rogue, or (3) Mage\n");
	scanf("%i", &(stats.type));

	switch(type){
		case 1:
			//assign stats
			stats.maxHealth = 120;
			stats.currentHealth = stats.maxHealth;
			stats.maxStamina = 110;
			stats.currentStamina = stats.maxStamina;
			stats.maxMana = 100;
			stats.currentMana = stats.maxMana;

			//increase skills
			skills.slashing = 25;
			skills.blunt = 35;

			printf("You are a warrior!\n");
			break;
		case 2:
			//assign stats
			stats.maxHealth = 110;
			stats.currentHealth = stats.maxHealth;
			stats.maxStamina = 110;
			stats.currentStamina = stats.maxStamina;
			stats.maxMana = 110;
			stats.currentMana = stats.maxMana;

			//increase skills
			skills.speed = 25;
			skills.sneak = 35;

			printf("You are a rogue!\n");
			break;
		case 3:
			//assign stats
			stats.maxHealth = 100;
			stats.currentHealth = stats.maxHealth;
			stats.maxStamina = 100;
			stats.currentStamina = stats.maxStamina;
			stats.maxMana = 130;
			stats.currentMana = stats.maxMana;

			//increase skills
			skills.defmage = 25;
			skills.offmage = 35;

			printf("You are a mage!\n");
			break;
		default:
			printf("Error: Character is not a valid class.\n");
			return;
			break;		

		//assign skill points
		printf("Skills: \n\t slashing: %i \n\t );
	}
}

//get function for current level
