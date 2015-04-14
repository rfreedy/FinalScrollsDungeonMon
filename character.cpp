//Final Project		character.cpp	4/11/15		Author: Kurt Davis
//Player Character for FSDM game, implementation file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

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
	//TODO: draw player_texture to screen at coordinates
}

void Character::toggleVisibility(){
	setVisibility(!getVisibility());
}

int Character::isVisible(){
	return getVisibility();
}

//interactive character creation
void Character::createCharacter(){
	//TODO: convert to screen and GUI
	
	/*********text based version*********/
	
	//select class
	printf("Enter character class: (1) Warrior, (2) Rogue, or (3) Mage\n");
	scanf("%i", &(stats.type));

	switch(stats.type){
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
	}



	//assign skill points
	incSkills(15);
}

//get function for current level
int Character::getLevel(){
	return stats.level;
}

//increase level, distribute skill points
void Character::levelUp(){
	stats.level++;	//level up!

	//TODO:	convert the below to screen/dialogue box

	//distribute stats points
	incStats(2);	

	//distribute skill points
	incSkills(5);

	//free restoration of all stats!
	stats.currentHealth = stats.maxHealth;
	stats.currentStamina = stats.maxStamina;
	stats.currentMana = stats.maxMana;
	
}

//engage in combat, requires enemy as argument
void Character::fight(Enemy &opponent){
	//TODO: finish this function	

	return;
}

//helper function, interactively increase stats
void Character::incStats(int toAssign){
	int pointsleft = toAssign;
	int selectedstat = 0;		
	while(pointsleft > 0){		
		printf("Stats: \n\t 1.\thealth: %i \n\t 2.\tstamina: %i \n\t 3.\tmana: %i \n\n", stats.maxHealth, stats.maxStamina, stats.maxMana);
		printf("Add 5 stat points: ");
		scanf("%i", &selectedstat);

		switch(selectedstat){
			case 1:
				stats.maxHealth += 5;
				pointsleft--;
				break;
			case 2:
				stats.maxStamina += 5;
				pointsleft--;
				break;
			case 3:	
				stats.maxMana += 5;
				pointsleft--;
				break;
			default:
				printf("Not a valid selection, try again.\n");
				break;			
		}
	}
	printf("Done allocating %i points!\n", (toAssign*5));
	return;
}

//helper function, interactively increase skills
void Character::incSkills(int toAssign){
	int pointsleft = toAssign;
	int selectedskill = 0;		
	while(pointsleft > 0){		
		printf("Skills: \n\t 1.\tslashing: %i \n\t 2.\tblunt: %i \n\t 3.\tspeed: %i \n\t 4.\tsneak: %i \n\t 5.\toffensive magic: %i \n\t 6.\tdefensive magic: %i \n\n", skills.slashing, skills.blunt, skills.speed, skills.sneak, skills.offmage, skills.defmage);
		printf("Add a skill point: ");
		scanf("%i", &selectedskill);

		switch(selectedskill){
			case 1:
				skills.slashing++;
				pointsleft--;
				break;
			case 2:
				skills.blunt++;
				pointsleft--;
				break;
			case 3:	
				skills.speed++;
				pointsleft--;
				break;
			case 4:
				skills.sneak++;
				pointsleft--;
				break;
			case 5:
				skills.offmage++;
				pointsleft--;
				break;
			case 6:	
				skills.defmage++;
				pointsleft--;
				break;
			default:
				printf("Not a valid selection, try again.\n");
				break;			
		}
	}
	printf("Done allocating %i points!\n", toAssign);
	return;
}
