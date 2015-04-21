//Final Project		fsdmgame.cpp	4/11/15		Author: Kurt Davis
//Game Instance for FSDM game
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "fsdmgame.h"
#include "entity.h"
#include "character.h"
#include "enemy.h"
#include <iostream>
#include "winrend.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gRedMan[8];		//class for aninamted character
SDL_Rect gDragon[1];
TTF_Font* gFont = NULL;

void FSDMGame::start() {
	if(!init()){
		
		printf("Initialization failed!\n");
	}else{
		if(!loadMedia()){
			printf("Media loading failed!\n");
		}else{
			play();		
		}
	}
	return;
}

int FSDMGame::play(){
	std::cout <<"running the play function" << std::endl;	
	loaded_level = new FSDMLevel;
	std::cout << "loaded level?" << std::endl;
	if(!(*loaded_level).constructed())
	{
		printf("Level failed to load!\n");		
		return 1;
	}else{
		//Main loop flag
		bool quit = false;

		gamestate = 2;		//1: walking, 2: battle
		int firstround = 1;
		int combatround = 0;
		arrowState = 0;
		combat_menu_state = 0;
		int arrowPos[2][4] = {{330, 460, 330, 460}, {310, 310, 375, 375}};

		//Event handler
		SDL_Event e;
		std::cout << "about to load in character" << std::endl;
		//player1
		player1 = new Character;
		std::cout << "loaded in character, about to load in enemy" << std::endl;
		opponent = new Enemy;
		std::cout << "loaded in enemy" << std::endl;
		//The dot that will be moving around on the screen
		//Dot dot;

		//Level camera
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		//While application is running
		while( !quit )
		{
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
	
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

			

				//Move the dot
				
				player1->move( loaded_level->getTileSet() );
				player1->setCamera( camera );
				
	
				//Render level
				std::cout << "will it render the level?" << std::endl;
				loaded_level->render(camera, textures.gTileTexture);
				std::cout << "yes" << std::endl;
				/*
				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					(*(loaded_level).getTileSet())[ i ]->render( camera );
				}
				*/

				opponent->render(camera, textures.gDragonTexture);	//render dragon
				//opponent->render(gDragon[0], textures.gDragonTexture);	//render dragon

				//Render dot
				player1->render( camera, textures.gDotTexture );
				std::cout << "also rendered the player" << endl;
			}else if(gamestate == 2){	//combat
				
				//initialize combat instance if first round
				if(firstround){
					//start both combatants off with full stamina
					player1->refillStamina();
					opponent->refillStamina();
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
				}else{
					//printf("Battle over\n");
					if(player1->getCurrentHealth() <= 0){
						//gameover
					}
					//delete opponent

					//gamestate = 1;
				}
				

				//---render screen objects---
				//render battle scene
				textures.battleBackground->render(0, 0);				

				//render character/enemy stats

				//render actions menu
				if(combat_menu_state == 0){
					textures.attackTextTexture->render(345, 305);
					textures.abilityTextTexture->render(345, 370);
					//textures.optionTextTexture->render(480, 305);
					textures.escapeTextTexture->render(480, 370);
					textures.arrowTexture->render(arrowPos[0][arrowState], arrowPos[1][arrowState]);
				}else if(combat_menu_state == 1){
					//TODO: Notifications
				}else if(combat_menu_state == 2){
					/*
					textures.abil1TextTexture->render(345, 305);
					textures.abil2TextTexture->render(345, 370);
					textures.abil3TextTexture->render(480, 305);
					textures.abil4TextTexture->render(480, 370);
					textures.arrowTexture->render(arrowPos[0][arrowState], arrowPos[1][arrowState]);
					*/				
				}
			}
			//Update screen
			SDL_RenderPresent( gRenderer );
		}
		
		//Free resources and close SDL
		close();
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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

	//Free text
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool FSDMGame::loadMedia()
{
	//Loading success flag
	bool success = true;

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

	textures.gTileTexture = new LTexture;
	if(textures.gTileTexture == NULL){
		printf("Failed to allocate gTileTexture!\n");
		success = false;
	}

	textures.battleBackground = new LTexture;
	if(textures.battleBackground == NULL){
		printf("Failed to allocate battleBackground!\n");
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

	textures.arrowTexture = new LTexture;
	if(textures.arrowTexture == NULL){
		printf("Failed to allocate arrowTexture!\n");
		success = false;
	}

	//Load dot texture - replace with character texture
	if( !textures.gDotTexture->loadFromFile( "characters-2sizeChange.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	else
	{
		//Set top left sprite		FRONT
		gRedMan[ 0 ].x =   0;
		gRedMan[ 0 ].y =   0;
		gRedMan[ 0 ].w = 25*2;
		gRedMan[ 0 ].h = 25*2;

		//Set top right sprite
		gRedMan[ 1 ].x = 22*2;
		gRedMan[ 1 ].y =   0;
		gRedMan[ 1 ].w = 25*2;
		gRedMan[ 1 ].h = 25*2;
		
		//Set bottom left sprite	BACK
		gRedMan[ 2 ].x =   0;
		gRedMan[ 2 ].y = 25*2;
		gRedMan[ 2 ].w = 25*2;
		gRedMan[ 2 ].h = 25*2;

		//Set bottom right sprite
		gRedMan[ 3 ].x = 22*2;
		gRedMan[ 3 ].y = 25*2;
		gRedMan[ 3 ].w = 25*2;
		gRedMan[ 3 ].h = 25*2;

		//Set bottom left sprite	RIGHT
		gRedMan[ 4 ].x = 45*2;
		gRedMan[ 4 ].y = 0;
		gRedMan[ 4 ].w = 25*2;
		gRedMan[ 4 ].h = 25*2;

		//Set bottom right sprite
		gRedMan[ 5 ].x = 66*2;
		gRedMan[ 5 ].y = 0;
		gRedMan[ 5 ].w = 25*2;
		gRedMan[ 5 ].h = 25*2;

		//Set bottom left sprite	LEFT
		gRedMan[ 6 ].x = 44*2;
		gRedMan[ 6 ].y = 21*2;
		gRedMan[ 6 ].w = 24*2;
		gRedMan[ 6 ].h = 25*2;

		//Set bottom right sprite
		gRedMan[ 7 ].x = 66*2;
		gRedMan[ 7 ].y = 23*2;
		gRedMan[ 7 ].w = 25*2;
		gRedMan[ 7 ].h = 25*2;
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
		if( !textures.attackTextTexture->loadFromRenderedText("Attack", textColor)){
			printf("Falied to render attack text texture!\n");
			success = false;
		}

		if( !textures.abilityTextTexture->loadFromRenderedText("Ability", textColor)){
			printf("Falied to render attack text texture!\n");
			success = false;
		}

		if( !textures.escapeTextTexture->loadFromRenderedText("Escape", textColor)){
			printf("Falied to render attack text texture!\n");
			success = false;
		}

		if( !textures.optionTextTexture->loadFromRenderedText("Option", textColor)){
			printf("Falied to render attack text texture!\n");
			success = false;
		}
	}
	

	return success;
}

void FSDMGame::handleCombatEvent( SDL_Event& e , int menustate)
{
	switch(menustate){
		case 1:		
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
						if(arrowState < 2){
							arrowState += 2;
						}
						break;
					case SDLK_LEFT:
						if((arrowState == 3)){
							arrowState--;
						}
						break;
					case SDLK_RIGHT:
						if((arrowState == 2)){
							arrowState++;
						}
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
