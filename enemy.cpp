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

int Enemy::speedCheck(){
	return skills.speed;
}

//TODO
void Enemy::refilStamina();

void Enemy::defend(int base_damage){
	
	int damage = base_damage;	//base_damage could just be substituted, but this would make damage modification easier

	if(stats.currentHealth - damage > 0){
		//regular damage taken, no KO
		stats.currentHealth -= damage;
	}else{
		//KO enemy
		stats.currentHealth = 0;
	}
	return;
}

int Enemy::attack(int move_number){

	int output_damage = 0;	
	int attack_type = getBestAttack();	//1= slash, 2= blunt, 3= magic

	//calculate damage out
	switch(attack_type){
		case 1:		//slashing
			output_damage = (int)((skills.slashing * (0.33)) + (((double)1/move_number) * 0.5 * skills.sneak) + (0.025*stats.currentHealth) + (0.05*stats.currentStamina));
			break;
		case 2:		//blunt
			output_damage = (int)((skills.blunt * (0.33)) + (((double)1/move_number) * 0.5 * skills.sneak) + (0.05*stats.currentHealth) + (0.1*stats.currentStamina));
			break;
		case 3:		//magic
			output_damage = (int)((skills.offmage * 0.5) + ((double)1/move_number) * 0.25 * skills.sneak);
			break;
		default:
			printf("Error in enemy attack.\n");		//#DEBUG#
			break;
	}

	return output_damage;
}

//helper function for attack
int Enemy::getBestAttack(){
	int atktype = 1;
	int highSkill = skills.slashing;
	if(skills.blunt > highSkill){
		atktype = 2;
		highSkill = skills.blunt;
	}

	if(skills.offmage > highSkill){
		atktype = 3;
		highSkill = skills.offmage
	}
	
	return atktype;	//return indicator of best attack type
}
