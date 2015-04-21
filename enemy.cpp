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
	level_coordinates_x = 200;
	level_coordinates_y = 200;

	//TODO: init unit_texture
	    mBox.x = 200;
   	    mBox.y = 200;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

	currentClip = &gDragon[ 0 ];
}

//deconstructor
Enemy::~Enemy(){
	//TODO: free/delete unit_texture
}

//virtual render function, common to entities
void Enemy::render( SDL_Rect& camera, LTexture* gDragonTexture){
	//TODO: draw unit_texture to screen at coordinates
	gDragonTexture->render( level_coordinates_x - camera.x, level_coordinates_y - camera.y, currentClip );
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

void Enemy::refillStamina(){
	stats.currentStamina = stats.maxStamina;
}

void Enemy::refillMana(){
	stats.currentMana = stats.maxMana;
}

void Enemy::replenish(){
	//stamina allowance
	if((stats.currentStamina + 15) <= (stats.maxStamina)){
		stats.currentStamina += 15;	
	}else{
		stats.currentStamina = stats.maxStamina;
	}

	//mana allowance
	if((stats.currentMana + 20) <= (stats.maxMana)){
		stats.currentMana += 20;	
	}else{
		stats.currentMana = stats.maxMana;
	}

	return;
}


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

	int stamina_cost = 0;
	int mana_cost = 0;
	int output_damage = 0;
	
	int attack_type = getBestAttack();	//1= slash, 2= blunt, 3= magic

	//calculate damage out
	switch(attack_type){
		case 1:		//slashing
			output_damage = (int)((skills.slashing * (0.33)) + (((double)1/move_number) * 0.5 * skills.sneak) + (0.025*stats.currentHealth) + (0.05*stats.currentStamina));
			stamina_cost = 20;
			break;
		case 2:		//blunt
			output_damage = (int)((skills.blunt * (0.33)) + (((double)1/move_number) * 0.5 * skills.sneak) + (0.05*stats.currentHealth) + (0.1*stats.currentStamina));
			stamina_cost = 25;
			break;
		case 3:		//magic
			output_damage = (int)((skills.offmage * 0.5) + ((double)1/move_number) * 0.25 * skills.sneak);
			mana_cost = 25;			
			break;
		default:
			printf("Error in enemy attack.\n");		//#DEBUG#
			break;
	}
	
	//check if stamina/mana are sufficient to attack
	if((stats.currentStamina >= stamina_cost) && (stats.currentMana >= mana_cost)){
		//check passed, decrement stamina/mana and attack		
		stats.currentStamina -= stamina_cost;
		stats.currentMana -= mana_cost;
		return output_damage;
	}else{
		return -1;	//not enough stamina/mana, return indicator
	}
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
		highSkill = skills.offmage;
	}
	
	return atktype;	//return indicator of best attack type
}
