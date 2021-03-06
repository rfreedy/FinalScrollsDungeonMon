//Final Project		fsdmgame.h	4/11/15		Author: Kurt Davis
//Game Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#ifndef FSDMGAME_H
#define FSDMGAME_H

#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "LTexture.h"
#include "Tile.h"
#include "fsdmlevel.h"
#include "entity.h"
#include "character.h"
#include "enemy.h"


typedef struct Textures {
	LTexture *gDotTexture = NULL;
	LTexture *gTileTexture = NULL;		//terrain sprite sheet
	LTexture *gDragonTexture = NULL;
	LTexture *gBossTexture = NULL;

	//For battle screen
	LTexture *battleBackground = NULL;
	
	LTexture *player1health = NULL;
	LTexture *player1stamina = NULL;
	LTexture *player1mana = NULL;

	LTexture *opponenthealth = NULL;
	LTexture *opponentstamina = NULL;
	LTexture *opponentmana = NULL;

	LTexture *attackTextTexture = NULL;
	LTexture *abilityTextTexture = NULL;
	LTexture *escapeTextTexture = NULL;
	LTexture *optionTextTexture = NULL;

	LTexture *abil0TextTexture = NULL;
	LTexture *abil1TextTexture = NULL;
	LTexture *abil2TextTexture = NULL;
	LTexture *abil3TextTexture = NULL;

	LTexture *arrowTexture = NULL;
	
	//game over messages
	LTexture *gameOverWinTextTexture = NULL;
	LTexture *gameOverLoseTextTexture = NULL;
	
	//character creation
	LTexture *startTextTexture = NULL;
	LTexture *warriorTextTexture = NULL;
	LTexture *rogueTextTexture = NULL;
	LTexture *wizardTextTexture = NULL;

	//level up screen 1
	LTexture *statsMessageTextTexture = NULL;
	LTexture *healthTextTexture = NULL;
	LTexture *staminaTextTexture = NULL;
	LTexture *manaTextTexture = NULL;

	//level up screen 2
	LTexture *skillsMessageTextTexture = NULL;
	LTexture *slashingTextTexture = NULL;
	LTexture *bluntTextTexture = NULL;
	LTexture *speedTextTexture = NULL;
	LTexture *sneakTextTexture = NULL;
	LTexture *offmageTextTexture = NULL;
	LTexture *defmageTextTexture = NULL;
	
	LTexture *notifTextTexture = NULL;
} Texture_type;


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class FSDMGame{
	public:
		//FSDMGame();
		//~FSDMGame();

		void start();
		int play();
		bool init();
		void close();
		bool loadMedia();
	
		void handleCombatEvent( SDL_Event& );
		void handleStartEvent( SDL_Event& );
		void handleLevelEvent( SDL_Event& );
		int findOpponent();

		void updateNotificationText(string);

		void updateStatText();
		void updateLevelText(int);
		void loadEnemies(string);

		//SDL_Rect gRedMan[8];		//class for aninamted character
	private:
		FSDMLevel *loaded_level = NULL;
		Texture_type textures;
		Character *player1 = NULL;
		Enemy *opponent = NULL;
		int gamestate;
		int current_level;
		int arrowState;
		int combat_menu_state;		//0: top level, 1: abilities, 2: notification
		int combat_action;		//0: nothing, 1: attack
		int reflect_flag;
		int level_menu_state;
		int points_remaining;		//for distributing points at levelup
		int characterType; //0 = warrior, 1 = rogue, 2 = wizard
		string notification_message;		//0: nothing, 1: attack
		SDL_Rect gDragon[1];	//1	down
		SDL_Rect gYetti[1];	//2	down
		SDL_Rect gSkeleton[1];	//3	down
		SDL_Rect gMonster[1];	//4	down
		SDL_Rect gCyclops[1];	//5	right
		SDL_Rect gKnight[1];	//6	left
		SDL_Rect gBae[1];	//7	left
		Enemy *enemyList[10];
};

#endif
