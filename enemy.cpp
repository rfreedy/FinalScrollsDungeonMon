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
Enemy::Enemy(int s1, int s2,int s3,int s4,int s5,int s6,int s7,int s8,int s9,int s10,int s11,int s12,int s13,int s14,int c1,int c2,SDL_Rect p1): Entity(){

	//initialize values in skills/stats structs	
	skills.slashing = s1;
	skills.blunt = s2;
	skills.speed = s3;
	skills.sneak = s4;
	skills.offmage = s5;
	skills.defmage = s6;

	stats.type = s7;
	stats.level = s8;
	stats.currentHealth = s9;
	stats.maxHealth = s10;
	stats.currentStamina = s11;
	stats.maxStamina = s12;
	stats.currentMana = s13;
	stats.maxMana = s14;


	//TODO: init unit_texture
	    mBox.x = c1;
   	    mBox.y = c2;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

	currentClip = p1;
}

//deconstructor
/*Enemy::~Enemy(){
	//TODO: free/delete unit_texture
}*/

//virtual render function, common to entities
void Enemy::render( SDL_Rect& camera, LTexture* gDragonTexture){
	//TODO: draw unit_texture to screen at coordinates
	gDragonTexture->render( mBox.x - camera.x, mBox.y - camera.y, &currentClip );
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

int Enemy::getMaxHealth(){
	return stats.maxHealth;
}

int Enemy::getMaxStamina(){
	return stats.maxStamina;
}

int Enemy::getMaxMana(){
	return stats.maxMana;
}

int Enemy::speedCheck(){
	return skills.speed;
}

SDL_Rect Enemy::getMBox(){
	return mBox;
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
		return 0;	//not enough stamina/mana, return indicator
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

int Enemy::getXCoord(){
	return mBox.x;
}

int Enemy::getYCoord(){
	return mBox.y;
}
