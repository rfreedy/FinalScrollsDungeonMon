//Final Project		fsdmgame.cpp	4/11/15		Author: Kurt Davis
//Game Instance for FSDM game
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "fsdmgame.h"
#include "entity.h"
#include "character.h"
#include "enemy.h"
#include "winrend.h"
#include <vector>
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gRedMan[8];		//class for aninamted character
TTF_Font* gFont = NULL;

void FSDMGame::start() {
	for(int j = 0; j < 10; j++){	
		enemyList[j] = NULL;
	}

	if(!init()){
		printf("Initialization failed!\n");
	}else{
		if(!loadMedia()){
			printf("Media loading failed!\n");
		}else{
			play();
			//cout << "Done playing." << endl;	//#DEBUG#	
		}
	}
	return;
}

int FSDMGame::play(){
	int opNum;
	//cout <<"Playing..." << endl;		//#DEBUG#	
	loaded_level = new FSDMLevel;
	//cout << "Level Created..." << endl;	//#DEBUG#
	//gamestate = 2;
	if(!loaded_level->constructed())
	{
		printf("Level failed to load!\n");		
		return 1;
	}else{
		//Game State Variables
		bool quit = false;	//Main loop flag
		gamestate = 0;		//0: start screen, 1: walking, 2: battle, 3: win, 4: lose, 5: level up
		arrowState = 0;
		combat_menu_state = 0;
		combat_action = 0;
		int firstround = 1;
		int combatround = 0;
		
		//Render Location Variables		
		int menuPos[2][4] = {{345, 475, 345, 475}, {310, 310, 375, 375}};
		int playerStatPos[2][3] = {{50, 50, 50}, {300, 350, 400}};
		int opponentStatPos[2][3] = {{150, 150, 150}, {50, 75, 100}};
		int arrowPos[2][4] = {{330, 460, 330, 460}, {315, 315, 380, 380}};
		int startArrow[2][3] = {{57, 270, 483}, {220, 220, 220}};
		int startMenu[2][4] = {{233, 77, 290, 503}, {120, 220, 220, 220}};
		int levelArrow[2][6] = {{87, 87, 87, 87, 87, 87}, {100, 125, 150, 175, 200, 225}};
		int levelMenu[2][7] = {{100, 100, 100, 100, 100, 100, 100}, {100, 125, 150, 175, 200, 225, 25}};
		//Event handler
		SDL_Event e;

		//Create Default Character
		//cout << "Creating character..." << endl;	//#DEBUG#
		//Allocate and Load Enemies
		//cout << "Loading Enemy..." << endl;		//#DEBUG#
		loadEnemies("enemyLoad.dat");

		//Level camera
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		std::cout << "Camera created..." << std::endl;
		
		//While application is running
		while( !quit )
		{
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			//std::cout << "Renderer cleared..." << std::endl;
			//run current gamestate
			if(gamestate == 1){		//movement			
				//Handle events on queue
				
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Handle input for the dot
					player1->handleEvent( e );
				}

				std::cout << "Event queue polled..." << std::endl;	

				//check for levelup
				if(player1->checkLevelUp()){
					player1->levelUp();
					arrowState = 1;
					level_menu_state = 0;
					points_remaining = 3;
					updateLevelText(3);
					gamestate = 5;
				}

				//Move the player
				if (player1->move( loaded_level->getTileSet(), enemyList ) == 1) {	//collision detected
					opNum = findOpponent();
					cout<<"Health: "<<enemyList[opNum]->getCurrentHealth()<<endl;
					if(enemyList[opNum]->getCurrentHealth() == 0){
						gamestate=3;
					}
					else{
						opponent = enemyList[opNum];					
						gamestate = 2;
					}					
				}
				else if (player1->move( loaded_level->getTileSet(), enemyList ) == DUNGEON1) {
				// this means player1 is on the first staircase and a new level needs to be created
						cout<<"check1"<<endl;
						delete loaded_level;
						cout<<"check2"<<endl;
						for(int i=0; i<5; i++){
							//if(enemyList[i] != NULL){
							cout<<"check3"<<endl;
								delete enemyList[i];
								enemyList[i] = NULL;
							//}
						}
						loaded_level = new FSDMLevel(DUNGEON1); // this will create the first dungeon
						//std::cout << "loaded level?" << std::endl;
						if(!(*loaded_level).constructed())
							{
								//printf("Level failed to load!\n");		
								return 1;
							}
						loadEnemies("enemyLoad2.dat");
				}
				else if (player1->move( loaded_level->getTileSet(), enemyList ) == DUNGEON2) {
				// this means player1 is on the first staircase and a new level needs to be created
						delete loaded_level;				
						for(int i=0; i<5; i++){
							//if(enemyList[i] != NULL){
							cout<<"check3"<<endl;
								delete enemyList[i];
								enemyList[i] = NULL;
							//}
						}
						loaded_level = new FSDMLevel(DUNGEON2); // this will create the first dungeon
						//std::cout << "loaded level?" << std::endl;
						if(!(*loaded_level).constructed())
							{
								//printf("Level failed to load!\n");		
								return 1;
							}
						loadEnemies("enemyLoad3.dat");
				}
				else if (player1->move( loaded_level->getTileSet(), enemyList ) == OVERWORLD) {
				// this means player1 is on the first staircase and a new level needs to be created
						delete loaded_level;				
						for(int i=0; i<5; i++){
							//if(enemyList[i] != NULL){
							cout<<"check3"<<endl;
								delete enemyList[i];
								enemyList[i] = NULL;
							//}
						}
						loaded_level = new FSDMLevel(OVERWORLD); // this will create the first dungeon
						//std::cout << "loaded level?" << std::endl;
						if(!(*loaded_level).constructed())
							{
								//printf("Level failed to load!\n");		
								return 1;
							}
						loadEnemies("enemyLoad.dat");
				}
				player1->move( loaded_level->getTileSet(), enemyList );	//odd number of move functions
				std::cout << "Move function worked " << std::endl;
				player1->setCamera( camera );
				std::cout << "camer worked " << std::endl;
	
				//Render level
			//	std::cout << "will it render the level?" << std::endl;
				loaded_level->render(camera, textures.gTileTexture);
			//	std::cout << "yes" << std::endl;
				player1->render( camera, textures.gDotTexture );
				/*
				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					(*(loaded_level).getTileSet())[ i ]->render( camera );
				}
				*/
				if(enemyList[0] != NULL)
					enemyList[0]->render(camera, textures.gDragonTexture);	//render dragon
				if(enemyList[1] != NULL)
					enemyList[1]->render(camera, textures.gDragonTexture);
				if(enemyList[2] != NULL)
					enemyList[2]->render(camera, textures.gDragonTexture);
				if(enemyList[3] != NULL)
					enemyList[3]->render(camera, textures.gDragonTexture);
				if(enemyList[4] != NULL)
					enemyList[4]->render(camera, textures.gDragonTexture);
				if(enemyList[5] != NULL)
					enemyList[5]->render(camera, textures.gDragonTexture);
				if(enemyList[6] != NULL)
					enemyList[6]->render(camera, textures.gDragonTexture);
				if(enemyList[7] != NULL)
					enemyList[7]->render(camera, textures.gDragonTexture);
				//opponent->render(camera, textures.gDragonTexture);	//render dragon
				//opponent->render(gDragon[0], textures.gDragonTexture);	//render dragon


		}
		else if(gamestate == 2){	//combat
				
				//initialize combat instance if first round
				if(firstround){
					//start both combatants off with full stamina
					player1->refillStamina();
					//opponent->refillStamina();
					firstround = 0;
					combatround = 0;
				}
				


				//---handle events in queue---				
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//handle combat event
					handleCombatEvent( e );
				}

				//perform combat round				
				
				
				//while enemy is alive
				
				if((opponent->getCurrentHealth() > 0) && (player1->getCurrentHealth() > 0)){
				
					if(combat_action){
						//check speed against enemy		
						if(opponent->speedCheck() > player1->speedCheck()){
							//opponent is faster, enemy moves first
							player1->defend(opponent->attack(combatround));
		
							//check for death
							if(player1->getCurrentHealth() <= 0){continue;};
					
							//player move
							opponent->defend(player1->attack(combatround));
			
						}else{
							//character is faster, player moves first
							opponent->defend(player1->attack(combatround));
			
							//check for death
							if(opponent->getCurrentHealth() <= 0){continue;};
				
							//opponent move
							player1->defend(opponent->attack(combatround));
						}
		
						//give stamina/mana allowances
						player1->replenish();
						opponent->replenish();

						combatround++;
						combat_action = 0;
					}


				}else{
					//printf("Battle over\n");
					if(opponent->getCurrentHealth() <= 0){
						//combat_menu_state = 2;
						//notification_message = "You defeated the enemy!"; ****** fix this
						gamestate = 1;
						delete enemyList[opNum];
						enemyList[opNum] = NULL;
						
						player1->addxp(15);
					}

					//If the player's health is 0, go to game state 4 ie game over lose state
					if(player1->getCurrentHealth() <= 0){
						gamestate=4;
					}
					//delete opponent

					//gamestate = 1;
				}
				

				//---render screen objects---
				//render battle scene
				textures.battleBackground->render(0, 0);
				
				//render character/enemy stats	
				updateStatText();
				textures.player1health->render(playerStatPos[0][0], playerStatPos[1][0]);
				textures.player1stamina->render(playerStatPos[0][1], playerStatPos[1][1]);
				textures.player1mana->render(playerStatPos[0][2], playerStatPos[1][2]);			

				textures.opponenthealth->render(opponentStatPos[0][0], opponentStatPos[1][0]);
				textures.opponentstamina->render(opponentStatPos[0][1], opponentStatPos[1][1]);
				textures.opponentmana->render(opponentStatPos[0][2], opponentStatPos[1][2]);	
				
				//render actions menu
				if(combat_menu_state == 0){
					textures.attackTextTexture->render(menuPos[0][0], menuPos[1][0]);
					textures.abilityTextTexture->render(menuPos[0][2], menuPos[1][2]);
					textures.escapeTextTexture->render(menuPos[0][1], menuPos[1][1]);
					textures.arrowTexture->render(arrowPos[0][arrowState], arrowPos[1][arrowState]);
				}else if(combat_menu_state == 1){
					textures.abil0TextTexture->render(menuPos[0][0], menuPos[1][0]);
					textures.abil1TextTexture->render(menuPos[0][1], menuPos[1][1]);
					textures.abil2TextTexture->render(menuPos[0][2], menuPos[1][2]);
					textures.abil3TextTexture->render(menuPos[0][3], menuPos[1][3]);
					textures.arrowTexture->render(arrowPos[0][arrowState], arrowPos[1][arrowState]);
				}else if(combat_menu_state == 2){
					//notification
					//updateNotificationText();
				}
				
			} else if(gamestate == 3) {
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
				//textures.battleBackground->render(0,0);
				//textures.gameOverWinTextTexture->render(200,200);
				loaded_level->render(camera, textures.gTileTexture);
				textures.gameOverWinTextTexture->render(200,200);

			} else if(gamestate == 4) {
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
				loaded_level->render(camera, textures.gTileTexture);
				textures.gameOverLoseTextTexture->render(200,200);
			} else if (gamestate == 0) {
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					handleStartEvent(e);
				}
				textures.startTextTexture->render(startMenu[0][0], startMenu[1][0]);
				textures.warriorTextTexture->render(startMenu[0][1], startMenu[1][1]);
				textures.rogueTextTexture->render(startMenu[0][2], startMenu[1][2]);
				textures.wizardTextTexture->render(startMenu[0][3], startMenu[1][3]);
				textures.arrowTexture->render(startArrow[0][arrowState], startArrow[1][arrowState]);
			} else if (gamestate == 5){	//levelup

				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					handleLevelEvent(e);
				}
				
				if(level_menu_state == 0){	//stats page		
					textures.statsMessageTextTexture->render(levelMenu[0][6], levelMenu[1][6]);
					textures.healthTextTexture->render(levelMenu[0][0], levelMenu[1][0]);
					textures.staminaTextTexture->render(levelMenu[0][1], levelMenu[1][1]);
					textures.manaTextTexture->render(levelMenu[0][2], levelMenu[1][2]);
					textures.arrowTexture->render(levelArrow[0][arrowState-1], levelArrow[1][arrowState-1]);
				}else if(level_menu_state == 1){	//skills page
					textures.skillsMessageTextTexture->render(levelMenu[0][6], levelMenu[1][6]);
					textures.slashingTextTexture->render(levelMenu[0][0], levelMenu[1][0]);
					textures.bluntTextTexture->render(levelMenu[0][1], levelMenu[1][1]);
					textures.speedTextTexture->render(levelMenu[0][2], levelMenu[1][2]);
					textures.sneakTextTexture->render(levelMenu[0][3], levelMenu[1][3]);
					textures.offmageTextTexture->render(levelMenu[0][4], levelMenu[1][4]);
					textures.defmageTextTexture->render(levelMenu[0][5], levelMenu[1][5]);
					textures.arrowTexture->render(levelArrow[0][arrowState-1], levelArrow[1][arrowState-1]);
				}
			}
			//Update screen
			SDL_RenderPresent( gRenderer );
		}
		
		//Free resources and close SDL
		close();
		cout << "Program Done!" << endl;
		cout << "Game Over!!" << endl;
		return 0;
	}
}

bool FSDMGame::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "FinalScrollsDungeonMon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				
				
				if(TTF_Init() == -1){
					printf("SDL_ttf coould not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
				
			}
		}
	}

	return success;
}



void FSDMGame::close()
{
	cout << "Closing..." << endl;
	for(int j = 0; j < 10; j++){
		delete enemyList[j];	
		enemyList[j] = NULL;
	}
	
	loaded_level->free();
	delete loaded_level;	
	loaded_level = NULL;	

	//Free loaded images
	
	textures.gDotTexture->free();
	delete textures.gDotTexture;
	textures.gDotTexture = NULL;

	textures.gTileTexture->free();
	delete textures.gTileTexture;
	textures.gTileTexture = NULL;

	textures.player1health->free();
	delete textures.player1health;
	textures.player1health = NULL;

	textures.player1stamina->free();
	delete textures.player1stamina;
	textures.player1stamina = NULL;

	textures.player1mana->free();
	delete textures.player1mana;
	textures.player1mana = NULL;

	textures.opponenthealth->free();
	delete textures.opponenthealth;
	textures.opponenthealth = NULL;

	textures.opponentstamina->free();
	delete textures.opponentstamina;
	textures.opponentstamina = NULL;

	textures.opponentmana->free();
	delete textures.opponentmana;
	textures.opponentmana = NULL;

	textures.battleBackground->free();
	delete textures.battleBackground;
	textures.battleBackground = NULL;

	textures.attackTextTexture->free();
	delete textures.attackTextTexture;
	textures.attackTextTexture = NULL;

	textures.abilityTextTexture->free();
	delete textures.abilityTextTexture;
	textures.abilityTextTexture = NULL;

	textures.escapeTextTexture->free();
	delete textures.escapeTextTexture;
	textures.escapeTextTexture = NULL;

	textures.optionTextTexture->free();
	delete textures.optionTextTexture;
	textures.optionTextTexture = NULL;

	textures.arrowTexture->free();
	delete textures.arrowTexture;
	textures.arrowTexture = NULL;	

	textures.gDragonTexture->free();
	delete textures.gDragonTexture;
	textures.gDragonTexture = NULL;
	
	textures.gameOverWinTextTexture->free();
	delete textures.gameOverWinTextTexture;
	textures.gameOverWinTextTexture = NULL;

	textures.gameOverLoseTextTexture->free();
	delete textures.gameOverLoseTextTexture;
	textures.gameOverLoseTextTexture = NULL;

	textures.startTextTexture->free();
	delete textures.startTextTexture;
	textures.startTextTexture = NULL;

	textures.warriorTextTexture->free();
	delete textures.warriorTextTexture;
	textures.warriorTextTexture = NULL;

	textures.rogueTextTexture->free();
	delete textures.rogueTextTexture;
	textures.rogueTextTexture = NULL;

	textures.wizardTextTexture->free();
	delete textures.wizardTextTexture;
	textures.wizardTextTexture = NULL;

	//level up screen 1
	textures.statsMessageTextTexture->free();
	delete textures.statsMessageTextTexture;
	textures.statsMessageTextTexture = NULL;
	
	textures.healthTextTexture->free();
	delete textures.healthTextTexture;
	textures.healthTextTexture = NULL;

	textures.staminaTextTexture->free();
	delete textures.staminaTextTexture;
	textures.staminaTextTexture = NULL;
	
	textures.manaTextTexture->free();
	delete textures.manaTextTexture;
	textures.manaTextTexture = NULL;

	//level up screen 2
	textures.skillsMessageTextTexture->free();
	delete textures.skillsMessageTextTexture;
	textures.skillsMessageTextTexture = NULL;

	textures.slashingTextTexture->free();
	delete textures.slashingTextTexture;
	textures.slashingTextTexture = NULL;

	textures.bluntTextTexture->free();
	delete textures.bluntTextTexture;
	textures.bluntTextTexture = NULL;

	textures.speedTextTexture->free();
	delete textures.speedTextTexture;
	textures.speedTextTexture = NULL;

	textures.sneakTextTexture->free();
	delete textures.sneakTextTexture;
	textures.sneakTextTexture = NULL;

	textures.offmageTextTexture->free();
	delete textures.offmageTextTexture;
	textures.offmageTextTexture = NULL;

	textures.defmageTextTexture->free();
	delete textures.defmageTextTexture;
	textures.defmageTextTexture = NULL;

	cout << "Textures freed..." << endl;

	//Free text
	TTF_CloseFont(gFont);
	gFont = NULL;

	cout << "Font closed..." << endl;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	cout << "Renderer and Window Destroyed..." << endl;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	
	cout << "Returning close function..." << endl;
}

bool FSDMGame::loadMedia()
{
	//Loading success flag
	bool success = true;

	//-------Character Textures-------
	//character texture
	textures.gDotTexture = new LTexture;
	if(textures.gDotTexture == NULL){
		printf("Failed to allocate gDotTexture!\n");
		success = false;
	}

	textures.gDragonTexture = new LTexture;
	if(textures.gDragonTexture == NULL){
		printf("Failed to allocate gDragonTexture!\n");
		success = false;
	}

	textures.gBossTexture = new LTexture;
	if(textures.gBossTexture == NULL){
		printf("Failed to allocate gBossTexture!\n");
		success = false;
	}

	
	//-------Map Textures-------
	//tile sprite sheet
	textures.gTileTexture = new LTexture;
	if(textures.gTileTexture == NULL){
		printf("Failed to allocate gTileTexture!\n");
		success = false;
	}


	//-------Battle Scene Textures-------
	//Panel outlines, displayed in background
	textures.battleBackground = new LTexture;
	if(textures.battleBackground == NULL){
		printf("Failed to allocate battleBackground!\n");
		success = false;
	}


	//-------Text Textures-------	
	textures.player1health = new LTexture;
	if(textures.player1health == NULL){
		printf("Failed to allocate player1health!\n");
		success = false;
	}

	textures.player1stamina = new LTexture;
	if(textures.player1stamina == NULL){
		printf("Failed to allocate player1stamina!\n");
		success = false;
	}

	textures.player1mana = new LTexture;
	if(textures.player1mana == NULL){
		printf("Failed to allocate player1mana!\n");
		success = false;
	}

	textures.opponenthealth = new LTexture;
	if(textures.opponenthealth == NULL){
		printf("Failed to allocate opponenthealth!\n");
		success = false;
	}

	textures.opponentstamina = new LTexture;
	if(textures.opponentstamina == NULL){
		printf("Failed to allocate opponentstamina!\n");
		success = false;
	}

	textures.opponentmana = new LTexture;
	if(textures.opponentmana == NULL){
		printf("Failed to allocate opponhttps://github.com/rfreedy/FinalScrollsDungeonMon.gitentmana!\n");
		success = false;
	}

	textures.attackTextTexture = new LTexture;
	if(textures.attackTextTexture == NULL){
		printf("Failed to allocate attackTextTexture!\n");
		success = false;
	}

	textures.abilityTextTexture = new LTexture;
	if(textures.abilityTextTexture == NULL){
		printf("Failed to allocate abilityTextTexture!\n");
		success = false;
	}

	textures.escapeTextTexture = new LTexture;
	if(textures.escapeTextTexture == NULL){
		printf("Failed to allocate escapeTextTexture!\n");
		success = false;
	}

	textures.optionTextTexture = new LTexture;
	if(textures.optionTextTexture == NULL){
		printf("Failed to allocate optionTextTexture!\n");
		success = false;
	}

	textures.abil0TextTexture = new LTexture;
	if(textures.abil0TextTexture == NULL){
		printf("Failed to allocate abil0TextTexture!\n");
		success = false;
	}

	textures.abil1TextTexture = new LTexture;
	if(textures.abil1TextTexture == NULL){
		printf("Failed to allocate abil1TextTexture!\n");
		success = false;
	}

	textures.abil2TextTexture = new LTexture;
	if(textures.abil2TextTexture == NULL){
		printf("Failed to allocate abil2TextTexture!\n");
		success = false;
	}

	textures.abil3TextTexture = new LTexture;
	if(textures.abil1TextTexture == NULL){
		printf("Failed to allocate abil3TextTexture!\n");
		success = false;
	}

	textures.arrowTexture = new LTexture;
	if(textures.arrowTexture == NULL){
		printf("Failed to allocate arrowTexture!\n");
		success = false;
	}

	textures.gameOverWinTextTexture = new LTexture;
	if(textures.gameOverWinTextTexture == NULL){
		printf("Failed to allocate gameOverWinTextTexture!\n");
		success = false;
	}

	textures.gameOverLoseTextTexture = new LTexture;
	if(textures.gameOverLoseTextTexture == NULL){
		printf("Failed to allocate gameOverLoseTextTexture!\n");
		success = false;
	}

	textures.startTextTexture = new LTexture;
	if(textures.startTextTexture == NULL){
		printf("Failed to allocate startTextTexture!\n");
		success = false;
	}

	textures.warriorTextTexture = new LTexture;
	if(textures.warriorTextTexture == NULL){
		printf("Failed to allocate warriorTextTexture!\n");
		success = false;
	}

	textures.rogueTextTexture = new LTexture;
	if(textures.rogueTextTexture == NULL){
		printf("Failed to allocate rogueTextTexture!\n");
		success = false;
	}

	textures.wizardTextTexture = new LTexture;
	if(textures.wizardTextTexture == NULL){
		printf("Failed to allocate wizardTextTexture!\n");
		success = false;
	}

	textures.statsMessageTextTexture = new LTexture;
	if(textures.statsMessageTextTexture == NULL){
		printf("Failed to allocate statsMessageTextTexture!\n");
		success = false;
	}

	textures.healthTextTexture = new LTexture;
	if(textures.healthTextTexture == NULL){
		printf("Failed to allocate healthTextTexture!\n");
		success = false;
	}

	textures.staminaTextTexture = new LTexture;
	if(textures.staminaTextTexture == NULL){
		printf("Failed to allocate staminaTextTexture!\n");
		success = false;
	}

	textures.manaTextTexture = new LTexture;
	if(textures.manaTextTexture == NULL){
		printf("Failed to allocate manaTextTexture!\n");
		success = false;
	}

	textures.skillsMessageTextTexture = new LTexture;
	if(textures.skillsMessageTextTexture == NULL){
		printf("Failed to allocate skillsMessageTextTexture!\n");
		success = false;
	}

	textures.slashingTextTexture = new LTexture;
	if(textures.slashingTextTexture == NULL){
		printf("Failed to allocate slashingTextTexture!\n");
		success = false;
	}

	textures.bluntTextTexture = new LTexture;
	if(textures.bluntTextTexture == NULL){
		printf("Failed to allocate bluntTextTexture!\n");
		success = false;
	}

	textures.speedTextTexture = new LTexture;
	if(textures.speedTextTexture == NULL){
		printf("Failed to allocate speedTextTexture!\n");
		success = false;
	}

	textures.sneakTextTexture = new LTexture;
	if(textures.sneakTextTexture == NULL){
		printf("Failed to allocate sneakTextTexture!\n");
		success = false;
	}

	textures.offmageTextTexture = new LTexture;
	if(textures.offmageTextTexture == NULL){
		printf("Failed to allocate offmageTextTexture!\n");
		success = false;
	}

	textures.defmageTextTexture = new LTexture;
	if(textures.defmageTextTexture == NULL){
		printf("Failed to allocate defmageTextTexture!\n");
		success = false;
	}
	//-------***Load Textures***-------

	//Load dot texture - replace with character texture
	if( !textures.gDotTexture->loadFromFile( "characters-2sizeChange.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	else
	{
		//Set top left sprite		FRONT
		gRedMan[ 0 ].x =   196;
		gRedMan[ 0 ].y =   107;
		gRedMan[ 0 ].w = 35;
		gRedMan[ 0 ].h = 40;

		//Set top right spriten
		gRedMan[ 1 ].x =  239;
		gRedMan[ 1 ].y =  107;
		gRedMan[ 1 ].w =  35;
		gRedMan[ 1 ].h =  40;
		
		//Set bottom left sprite	BACK
		gRedMan[ 2 ].x =   196;
		gRedMan[ 2 ].y =   160;
		gRedMan[ 2 ].w =    35;
		gRedMan[ 2 ].h =    40;

		//Set bottom right sprite
		gRedMan[ 3 ].x = 235;
		gRedMan[ 3 ].y = 160;
		gRedMan[ 3 ].w = 35;
		gRedMan[ 3 ].h = 40;

		//Set bottom left sprite	RIGHT
		gRedMan[ 4 ].x = 283;
		gRedMan[ 4 ].y = 105;
		gRedMan[ 4 ].w = 35;
		gRedMan[ 4 ].h = 40;

		//Set bottom right sprite
		gRedMan[ 5 ].x = 328;
		gRedMan[ 5 ].y = 105;
		gRedMan[ 5 ].w = 35;
		gRedMan[ 5 ].h = 40;

		//Set bottom left sprite	LEFT

		gRedMan[ 6 ].x = 282;
		gRedMan[ 6 ].y = 158;
		gRedMan[ 6 ].w = 30;
		gRedMan[ 6 ].h = 40;

		//Set bottom right sprite
		gRedMan[ 7 ].x = 323;
		gRedMan[ 7 ].y = 158;
		gRedMan[ 7 ].w = 30;
		gRedMan[ 7 ].h = 40;
	}

	if( !textures.gDragonTexture->loadFromFile( "characters-2sizeChange.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	else
	{
		gDragon[0].x = 412*2;
		gDragon[0].y = 100*2;
		gDragon[0].w = 25*2;
		gDragon[0].h = 25*2;

		gYetti[0].x = 448*2;
		gYetti[0].y = 240*2;
		gYetti[0].w = 25*2;
		gYetti[0].h = 25*2;

		gSkeleton[0].x = 250*2;
		gSkeleton[0].y = 75*2;
		gSkeleton[0].w = 25*2;
		gSkeleton[0].h = 25*2;

		gMonster[0].x = 405*2;
		gMonster[0].y = 175*2;
		gMonster[0].w = 25*2;
		gMonster[0].h = 25*2;

		gCyclops[0].x = 50*2;
		gCyclops[0].y = 145*2;
		gCyclops[0].w = 25*2;
		gCyclops[0].h = 25*2;

		gKnight[0].x = 295*2;
		gKnight[0].y = 375*2;
		gKnight[0].w = 25*2;
		gKnight[0].h = 25*2;

		gBae[0].x = 345*2;
		gBae[0].y = 375*2;
		gBae[0].w = 25*2;
		gBae[0].h = 25*2;
		
	}
	//Load tile texture - replace with our tile sprite sheet
	if( !textures.gTileTexture->loadFromFile( "tileSpritesSizeChange.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	
	if( !textures.battleBackground->loadFromFile( "combatscreenfull.png" ) )
	{
		printf( "Failed to combat state texture!\n" );
		success = false;
	}

	
	if( !textures.arrowTexture->loadFromFile( "arrow.png" ) )
	{
		printf( "Failed to escape text texture!\n" );
		success = false;
	}
	

	
	//open font Xerox_Sans_Serif_Narrow
	gFont = TTF_OpenFont("Xerox_Sans_Serif_Narrow.ttf", 24);
	if(gFont == NULL){
		printf("Falied to load from font file! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}else{
		//initialize text textures
		SDL_Color textColor = {0, 0, 0};
		SDL_Color textColorWhite = {255, 255, 255};
		if( !textures.attackTextTexture->loadFromRenderedText("Attack", textColor)){
			printf("Falied to render attack text texture!\n");
			success = false;
		}

		if( !textures.abilityTextTexture->loadFromRenderedText("Ability", textColor)){
			printf("Falied to render ability text texture!\n");
			success = false;
		}

		if( !textures.escapeTextTexture->loadFromRenderedText("Escape", textColor)){
			printf("Falied to render escape text texture!\n");
			success = false;
		}

		if( !textures.optionTextTexture->loadFromRenderedText("Option", textColor)){
			printf("Falied to render option text texture!\n");
			success = false;
		}

		if( !textures.abil0TextTexture->loadFromRenderedText("Heal", textColor)){
			printf("Falied to render abil0 text texture!\n");
			success = false;
		}

		if( !textures.abil1TextTexture->loadFromRenderedText("Shield", textColor)){
			printf("Falied to render abil1 text texture!\n");
			success = false;
		}

		if( !textures.abil2TextTexture->loadFromRenderedText("Debuff", textColor)){
			printf("Falied to render abil2 text texture!\n");
			success = false;
		}

		if( !textures.abil3TextTexture->loadFromRenderedText("Spell Thing", textColor)){
			printf("Falied to render abil3 text texture!\n");
			success = false;
		}

		if( !textures.gameOverWinTextTexture->loadFromRenderedText("You Saved The Princess!", textColorWhite)){
			printf("Falied to render game Over text texture!\n");
			success = false;
		}

		if( !textures.gameOverLoseTextTexture->loadFromRenderedText("Game Over!", textColorWhite)){
			printf("Falied to render game Over text texture!\n");
			success = false;
		}

		if( !textures.startTextTexture->loadFromRenderedText("Choose Your Class: ", textColor)){
			printf("Falied to render game Over text texture!\n");
			success = false;
		}

		if( !textures.warriorTextTexture->loadFromRenderedText("Warrior", textColor)){
			printf("Falied to render warrior text texture!\n");
			success = false;
		}

		if( !textures.rogueTextTexture->loadFromRenderedText("Rogue", textColor)){
			printf("Falied to render rogue text texture!\n");
			success = false;
		}

		if( !textures.wizardTextTexture->loadFromRenderedText("Wizard", textColor)){
			printf("Falied to render wizard text texture!\n");
			success = false;
		}

		if( !textures.statsMessageTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render stats message text texture!\n");
			success = false;
		}

		if( !textures.healthTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render health text texture!\n");
			success = false;
		}

		if( !textures.staminaTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render stamina text texture!\n");
			success = false;
		}

		if( !textures.manaTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render mana text texture!\n");
			success = false;
		}	

		if( !textures.skillsMessageTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render skills message text texture!\n");
			success = false;
		}

		if( !textures.slashingTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render slashing text texture!\n");
			success = false;
		}

		if( !textures.bluntTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render blunt text texture!\n");
			success = false;
		}

		if( !textures.speedTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render speed text texture!\n");
			success = false;
		}

		if( !textures.sneakTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render sneak text texture!\n");
			success = false;
		}

		if( !textures.offmageTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render offmage text texture!\n");
			success = false;
		}

		if( !textures.defmageTextTexture->loadFromRenderedText("Empty", textColor)){
			printf("Falied to render defmage text texture!\n");
			success = false;
		}

	}

	/*gFont = TTF_OpenFont("Xerox_Sans_Serif_Narrow.ttf", 24);
	if(gFont == NULL){
		printf("Falied to load from font file! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	} else{
		SDL_Color textColor = {0, 0, 0};
		if( !textures.gameOverWinTextTexture->loadFromRenderedText("Game Over", textColor)){
			printf("Falied to render game Over text texture!\n");
			success = false;
		}
	}*/
	

	return success;
}

void FSDMGame::handleCombatEvent( SDL_Event& e)
{
	switch(combat_menu_state){
		case 0:		
			//If a key was pressed
			if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
				//change arrow location
				switch( e.key.keysym.sym ){
					case SDLK_UP:
						if(arrowState == 2){
							arrowState -= 2;
						}
						break;
					case SDLK_DOWN:
						if(arrowState == 0){
							arrowState += 2;
						}
						break;
					case SDLK_LEFT:
						if((arrowState == 1)){
							arrowState--;
						}
						break;
					case SDLK_RIGHT:
						if((arrowState == 0)){
							arrowState++;
						}
						break;
					case SDLK_RETURN:
						cout << "gamestate: "<<gamestate<<endl;
						cout << "arrow: "<<arrowState<<endl;
						if(arrowState == 0){
							combat_action = 1;	//attack
						}else if(arrowState == 1){
							gamestate = 1;		//escape combat
							cout << "gamestate: "<<gamestate<<endl;
						}else if(arrowState == 2){
							combat_menu_state = 1;	//enter abilities submenu
						}
						break;
					default:
						break;
				}
			}
			break;

		case 1:
			if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
				switch(e.key.keysym.sym){
					case SDLK_UP:
						if(arrowState > 1){
							arrowState -= 2;
						}
						break;
					case SDLK_DOWN:
						if(arrowState < 2){
							arrowState += 2;
						}
						break;
					case SDLK_LEFT:
						if((arrowState == 1) || (arrowState == 3)){
							arrowState--;
						}
						break;
					case SDLK_RIGHT:
						if((arrowState == 0) || (arrowState == 2)){
							arrowState++;
						}
						break;
					case SDLK_RETURN:
						//activate ability
						break;
					case SDLK_ESCAPE:
						//return to previous menu
						combat_menu_state = 0;
						break;
					default:
						break;
				}
			}
			break;
		
		case 2:
			if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
				switch(e.key.keysym.sym){
					case SDLK_RETURN:
						//activate ability
						break;
					default:
						break;
				}
			}
			break;

		default:
			break;
	}
}

void FSDMGame::handleStartEvent(SDL_Event &e) {

	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
		//change arrow location
		switch( e.key.keysym.sym ){	
			case SDLK_LEFT:
				if((arrowState == 1 || arrowState == 2)){
					arrowState--;
				}
				break;
			case SDLK_RIGHT:
				if((arrowState == 0 || arrowState == 1)){
					arrowState++;
				}
				break;
			case SDLK_RETURN:
				cout << "gamestate: "<<gamestate<<endl;
					cout << "arrow: "<<arrowState<<endl;
					gamestate = 1;
					if(arrowState == 0){
						characterType = 0;	//warrior
					}else if(arrowState == 1){
						characterType = 1;		//rogue
						cout << "gamestate: "<<gamestate<<endl;
					}else if(arrowState == 2){
						characterType = 2;	//wizard
					}	
					player1 = new Character(characterType);				
					break;
				default:
					break;
		}
	}
}

void FSDMGame::handleLevelEvent(SDL_Event &e){
	switch(level_menu_state){
		case 0:		//stats page	
			//If a key was pressed
			if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
				//change arrow location
				switch( e.key.keysym.sym ){
					case SDLK_UP:
						if(arrowState > 1){
							arrowState--;
						}
						break;
					case SDLK_DOWN:
						if(arrowState < 3){
							arrowState++;
						}
						break;
					case SDLK_RETURN:
						//cout << "gamestate: "<<gamestate<<endl;
						//cout << "arrow: "<<arrowState<<endl;
						if(points_remaining > 1){
							player1->incrementStat(arrowState);
							points_remaining--;
						}else{
							player1->incrementStat(arrowState);
							points_remaining = 10;
							arrowState = 1;
							level_menu_state = 1;	//advance to next screen
						}

						updateLevelText(points_remaining);
						break;
					default:
						break;
				}
			}
			break;

		case 1:		//skills page
			if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
				switch(e.key.keysym.sym){
					case SDLK_UP:
						if(arrowState > 1){
							arrowState--;
						}
						break;
					case SDLK_DOWN:
						if(arrowState < 6){
							arrowState++;
						}
						break;
					case SDLK_RETURN:
						//cout << "gamestate: "<<gamestate<<endl;
						//cout << "arrow: "<<arrowState<<endl;
						if(points_remaining > 1){
							player1->incrementSkill(arrowState);
							points_remaining--;
						}else{
							player1->incrementSkill(arrowState);
							points_remaining = 0;
							arrowState = 0;
							level_menu_state = 0;	//advance to next screen
							player1->refillAllStats();						
							gamestate = 1;
							break;
						}

						updateLevelText(points_remaining);
						break;
					default:
						break;
				}
			}
			break;
		default:
			break;
	}
}

//rebuild character and enemy stat textures
void FSDMGame::updateStatText(){
	bool success = true;

	//---Update player Stat Textures	
	stringstream convert1;
	stringstream convert2;
	stringstream convert3;

	string player1health_text;
	string player1stamina_text;
	string player1mana_text;

	convert1 << "Health: " << (player1->getCurrentHealth()) << "/" << (player1->getMaxHealth());
	player1health_text = convert1.str();

	convert2 << "Stamina: " << (player1->getCurrentStamina()) << "/" << (player1->getMaxStamina());
	player1stamina_text = convert2.str();

	convert3 << "Mana: " << (player1->getCurrentMana()) << "/" << (player1->getMaxMana());
	player1mana_text = convert3.str();

	SDL_Color textColor = {0, 0, 0};
	if( !textures.player1health->loadFromRenderedText(player1health_text, textColor)){
		printf("Falied to render player 1 health text texture!\n");
		success = false;
	}

	if( !textures.player1stamina->loadFromRenderedText(player1stamina_text, textColor)){
		printf("Falied to render player 1 stamina text texture!\n");
		success = false;
	}

	if( !textures.player1mana->loadFromRenderedText(player1mana_text, textColor)){
		printf("Falied to render player 1 mana text texture!\n");
		success = false;
	}				//case 4: pic = gRedMan[4]; break;

	//---Update Opponent Stat Textures
	if(opponent != NULL){
		stringstream convert4;
		stringstream convert5;
		stringstream convert6;

		string opponenthealth_text;
		string opponentstamina_text;
		string opponentmana_text;

		convert4 << "Health: " << (opponent->getCurrentHealth()) << "/" << (opponent->getMaxHealth());
		opponenthealth_text = convert4.str();

		convert5 << "Stamina: " << (opponent->getCurrentStamina()) << "/" << (opponent->getMaxStamina());
		opponentstamina_text = convert5.str();

		convert6 << "Mana: " << (opponent->getCurrentMana()) << "/" << (opponent->getMaxMana());
		opponentmana_text = convert6.str();

		if( !textures.opponenthealth->loadFromRenderedText(opponenthealth_text, textColor)){
			printf("Falied to render opponent health text texture!\n");
			success = false;
		}
	
		if( !textures.opponentstamina->loadFromRenderedText(opponentstamina_text, textColor)){
			printf("Falied to render opponent stamina text texture!\n");
			success = false;
		}
	
		if( !textures.opponentmana->loadFromRenderedText(opponentmana_text, textColor)){
			printf("Falied to render opponent mana text texture!\n");
			success = false;
		}
	}
}

void FSDMGame::updateLevelText(int remaining){
	bool success = true;

	//---Update player Stat Textures	
	stringstream convert0;	
	stringstream convert1;
	stringstream convert2;
	stringstream convert3;
	stringstream convert4;
	stringstream convert5;
	stringstream convert6;
	stringstream convert7;
	stringstream convert8;
	stringstream convert9;
	stringstream convert10;

	string message1;
	string health_text;
	string stamina_text;
	string mana_text;

	string message2;
	string slashing_text;
	string blunt_text;
	string speed_text;
	string sneak_text;
	string offmage_text;
	string defmage_text;

	convert0 << "Assign " << remaining << " stat points!";
	message1 = convert0.str();

	convert1 << "Health: " << (player1->getMaxHealth());
	health_text = convert1.str();

	convert2 << "Stamina: " << (player1->getMaxStamina());
	stamina_text = convert2.str();

	convert3 << "Mana: " << (player1->getMaxMana());
	mana_text = convert3.str();
	
	convert4 << "Assign " << remaining << " skill points!";
	message2 = convert4.str();

	convert5 << "Slashing: " << (player1->getSlashing());
	slashing_text = convert5.str();

	convert6 << "Blunt: " << (player1->getBlunt());
	blunt_text = convert6.str();

	convert7 << "Speed: " << (player1->speedCheck());
	speed_text = convert7.str();

	convert8 << "Sneak: " << (player1->getSneak());
	sneak_text = convert8.str();

	convert9 << "Offensive Magic: " << (player1->getOffmage());
	offmage_text = convert9.str();
	
	convert10 << "Defensive Magic: " << (player1->getDefmage());
	defmage_text = convert10.str();

	SDL_Color textColor = {0, 0, 0};
	if( !textures.statsMessageTextTexture->loadFromRenderedText(message1, textColor)){
		printf("Falied to render stats message text texture!\n");
		success = false;
	}

	if( !textures.healthTextTexture->loadFromRenderedText(health_text, textColor)){
		printf("Falied to render health text texture!\n");
		success = false;
	}

	if( !textures.staminaTextTexture->loadFromRenderedText(stamina_text, textColor)){
		printf("Falied to render stamina text texture!\n");
		success = false;
	}

	if( !textures.manaTextTexture->loadFromRenderedText(mana_text, textColor)){
		printf("Falied to render mana text texture!\n");
		success = false;
	}

	if( !textures.skillsMessageTextTexture->loadFromRenderedText(message2, textColor)){
		printf("Falied to render skills message text texture!\n");
		success = false;
	}

	if( !textures.slashingTextTexture->loadFromRenderedText(slashing_text, textColor)){
		printf("Falied to render slashing text texture!\n");
		success = false;
	}

	if( !textures.bluntTextTexture->loadFromRenderedText(blunt_text, textColor)){
		printf("Falied to render blunt text texture!\n");
		success = false;
	}

	if( !textures.speedTextTexture->loadFromRenderedText(speed_text, textColor)){
		printf("Falied to render speed text texture!\n");
		success = false;
	}

	if( !textures.sneakTextTexture->loadFromRenderedText(sneak_text, textColor)){
		printf("Falied to render sneak text texture!\n");
		success = false;
	}

	if( !textures.offmageTextTexture->loadFromRenderedText(offmage_text, textColor)){
		printf("Falied to render offmage text texture!\n");
		success = false;
	}

	if( !textures.defmageTextTexture->loadFromRenderedText(defmage_text, textColor)){
		printf("Falied to render defmage text texture!\n");
		success = false;
	}

}

void FSDMGame::loadEnemies(string file){
	//string file = "enemyLoad.dat";
	int count = 0;
	int num;
	int j = 0;
	
	vector<int> stats;
	int monsterPicCount = 0;
	SDL_Rect pic=gDragon[0];
	//SDL_Rect pic;
	ifstream myfile;			//data file for enemy input
	myfile.open(file.c_str());
		
	while(myfile>>num){
		stats.push_back(num);
		count++;
		if(count >=17){	//after 16 numbers are read
			monsterPicCount = stats[16];
			cout<<"monster count: "<<monsterPicCount<<endl;
			switch (monsterPicCount){
				case 1:	pic = gDragon[0]; break;
				case 2:	pic = gYetti[0]; break;
				case 3: pic = gSkeleton[0]; break;
				case 4: pic = gMonster[0]; break;
				case 5: pic = gCyclops[0]; break;
				case 6: pic = gKnight[0]; break;
				case 7: pic = gBae[0]; break;
				//default: pic = gDragon[0]; break;
			}
			count = 0;	//reset count
			//for(int i=j; i<5; i++){
			//cout <<"pic: "<<endl;
			for( vector<int>::const_iterator i = stats.begin(); i != stats.end(); ++i)
    				cout << *i << ' ';
			enemyList[j] = new Enemy(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], stats[7], stats[8], stats[9], stats[10], stats[11], stats[12], stats[13], stats[14], stats[15], pic);
			j++;	//increment enemyList
			stats.clear();	//clear stats vector
		}
	}
}

//returns index in enemyList of collided enemy
int FSDMGame::findOpponent(){
	int retVal = -1;	

	for(int i = 0; i < 10; i++){
		if(enemyList[i] != NULL){
			if((player1->getXCoord() <= enemyList[i]->getXCoord() + 30) && (player1->getXCoord() >= enemyList[i]->getXCoord() - 30)){
				if((player1->getYCoord() <= enemyList[i]->getYCoord() + 40) && (player1->getYCoord() >= enemyList[i]->getYCoord() - 40)){
					retVal = i;
				}
			}
		}
	}

	return retVal;
}

