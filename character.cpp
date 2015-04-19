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
#include "fsdmlevel.h"
#include "fsdmgame.h"

//default constructor
Character::Character(): Entity(){

	//initialize values in skills/stats structs	
	skills.slashing = 10;
	skills.blunt = 50;
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

	   //Initialize the collision box
    mBox.x = 0;
    mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

	count = 0;
	currentClip = &gRedMan[ 0 ];
	up =0;
	down = 0;
	left = 0;
	right = 0;
}

//deconstructor
Character::~Character(){
	//TODO: free/delete player_texture
	//FIXED: Deallocation of texture occurs in fsdgame.cpp
}

//draw stats panel in combat
//void Character::renderStats(){

//}

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

int Character::getCurrentHealth(){
	return stats.currentHealth;
}

int Character::getCurrentStamina(){
	return stats.currentStamina;
}

int Character::getCurrentMana(){
	return stats.currentMana;
}

int Character::speedCheck(){
	return skills.speed;
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
	
	//start both combatants off with full stamina
	refillStamina();
	opponent.refillStamina();

	int movecount = 0;

	//while enemy is alive
	while((opponent.getCurrentHealth() > 0) && (stats.currentHealth > 0)){

		//check speed against enemy		
		if(opponent.speedCheck() > skills.speed){
			//opponent is faster, enemy moves first
			defend(opponent.attack(movecount));

			//check for death
			if(stats.currentHealth <= 0){break;};
			
			//player move
			opponent.defend(attack(movecount));
		
		}else{
			//character is faster, player moves first
			opponent.defend(attack(movecount));

			//check for death
			if(opponent.getCurrentHealth() <= 0){break;};
			
			//opponent move
			defend(opponent.attack(movecount));
		}

		
		//give stamina/mana allowances
		replenish();
		opponent.replenish();

		movecount++;
	}

	return;
}

//helper for fight()
void Character::replenish(){
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

//sets currentStamina to maxStamina
void Character::refillStamina(){
	stats.currentStamina = stats.maxStamina;
}

//sets currentMana to maxMana
void Character::refillMana(){
	stats.currentMana = stats.maxMana;
}

void Character::defend(int base_damage){
	
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

int Character::attack(int move_number){

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
			printf("Error in player attack.\n");		//#DEBUG#
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
int Character::getBestAttack(){
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

/******Character Movement********/
void Character::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
           case SDLK_UP: 
		if(down ==0 && left == 0 && right ==0){
		up++;
		down = 0; left = 0; right = 0;
		//mBox.y = mBox.y - TILE_SIZE; 
		mVelY -= DOT_VEL; 
		if(count%2 == 0){
			currentClip = &gRedMan[ 2 ];
		}
		else{
			currentClip = &gRedMan[ 3 ];
		}
		//count++;
		}
		break;
		
            case SDLK_DOWN:
		if(up ==0 && left == 0 && right ==0){
		down++;
		up = 0;
		left =0; right = 0;
		//mBox.y = mBox.y + TILE_SIZE; 
		mVelY += DOT_VEL;
		if(count%2 == 0){
			currentClip = &gRedMan[ 0 ];
		}
		else{
			currentClip = &gRedMan[ 1 ];
		}
		//count++;
		}
		break;
            case SDLK_LEFT:
		if(down ==0 && up == 0 && right ==0){
		right = 0;
		up =0;
		down = 0;
		left++;
		//mBox.x = mBox.x - TILE_SIZE; 
		mVelX -= DOT_VEL; 
		if(count%2 == 0){
			currentClip = &gRedMan[ 6 ];
		}
		else{
			currentClip = &gRedMan[ 7 ];
		}
		}
		break;
            case SDLK_RIGHT:
		if(down ==0 && left == 0 && up ==0){
		left = 0;
		up = 0;
		down = 0;
		
		right++;
		//mBox.x = mBox.x + TILE_SIZE; 
		mVelX += DOT_VEL; 
		if(count%2 == 0){
			currentClip = &gRedMan[ 4 ];
		}
		else{
			currentClip = &gRedMan[ 5 ];
		}
		}
		break;

	case SDLK_RSHIFT:
		printf("up: %d\n", up);
		printf("down: %d\n", down);
		printf("left: %d\n", left);
		printf("right: %d\n\n", right);
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:if(down ==0 && left == 0 && right ==0){ mVelY =0; up = 0;} break;
            case SDLK_DOWN: if(up ==0 && left == 0 && right ==0){ mVelY =0; down = 0;} break;
            case SDLK_LEFT:if(down ==0 && up == 0 && right ==0){ mVelX =0; left = 0;} break;
            case SDLK_RIGHT: if(down ==0 && left == 0 && up ==0){ mVelX =0; right = 0;} break;
        }
    }
}

void Character::move( Tile *tiles[] )
{
    //Move the dot left or right
	//left =0;
	count++;		//increment count in move (continuous
	if (right > 0){		//update SDL_ract in move
		if(count%2 == 0){
			currentClip = &gRedMan[ 4 ];
		}
		else{
			currentClip = &gRedMan[ 5 ];
		}
	}
	else if (left >0){
		if(count%2 == 0){
			currentClip = &gRedMan[ 6 ];
		}
		else{
			currentClip = &gRedMan[ 7 ];
		}
	}
	else if(down > 0){
		if(count%2 == 0){
			currentClip = &gRedMan[ 0 ];
		}
		else{
			currentClip = &gRedMan[ 1 ];
		}
	}
	else if (up >0){
		if(count%2 == 0){
			currentClip = &gRedMan[ 2 ];
		}
		else{
			currentClip = &gRedMan[ 3 ];
		}
	}



    mBox.x += mVelX;
    //If the dot went too far to the left or right or touched a wall
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= mVelX;
	//mBox.x = mBox.x - TILE_SIZE;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.y -= mVelY;
	//mBox.y = mBox.y + TILE_SIZE;
    }
}

void Character::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Character::render( SDL_Rect& camera, LTexture* gDotTexture)
{
    //Show the dot
	gDotTexture->render( mBox.x - camera.x, mBox.y - camera.y, currentClip );
}
/*
//virtual render function, common to entities
void Character::render(){
	//TODO: draw player_texture to screen at coordinates
}
*/
bool Character::touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= TILE_SKINNYTREES ) && ( tiles[ i ]->getType() <= TILE_WATER ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

bool Character::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
