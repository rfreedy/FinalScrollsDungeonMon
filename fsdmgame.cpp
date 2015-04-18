//Final Project		fsdmgame.cpp	4/11/15		Author: Kurt Davis
//Game Instance for FSDM game
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "fsdmgame.h"
#include "entity.h"
#include "character.h"
#include "enemy.h"

#include "winrend.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gRedMan[8];		//class for aninamted character
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
	
	loaded_level = new FSDMLevel;
	if(!(*loaded_level).constructed())
	{
		printf("Level failed to load!\n");		
		return 1;
	}else{
		//Main loop flag
		bool quit = false;

		int gamestate = 2;
		int firstround = 1;
		int combatround = 0;

		//Event handler
		SDL_Event e;

		//player1
		player1 = new Character;

		Enemy opponent;

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
					//if(dot.getVely() == 0 && dot.getVelx() == 0)
					//Handle input for the dot
					//dot.handleEvent( e );
				}

			

				//Move the dot
				/*
				dot.move( loaded_level->getTileSet() );
				dot.setCamera( camera );
				*/
	
				//Render level
				//loaded_level->render(camera, textures.gTileTexture);

				/*
				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					(*(loaded_level).getTileSet())[ i ]->render( camera );
				}
				*/
	
				//Render dot
				//dot.render( camera, textures.gDotTexture );

			}else if(gamestate = 2){	//combat
				
				//initialize combat instance if first round
				if(firstround){
					//start both combatants off with full stamina
					player1->refillStamina();
					opponent.refillStamina();
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

					//character.handleCombatEvent();
				}

				//perform combat round				
				
				
				//while enemy is alive
				if((opponent.getCurrentHealth() > 0) && (player1->getCurrentHealth() > 0)){
		
	
					//check speed against enemy		
					if(opponent.speedCheck() > player1->speedCheck()){
						//opponent is faster, enemy moves first
						player1->defend(opponent.attack(combatround));
	
						//check for death
						if(player1->getCurrentHealth() <= 0){continue;};
				
						//player move
						opponent.defend(player1->attack(combatround));
		
					}else{
						//character is faster, player moves first
						opponent.defend(player1->attack(combatround));
		
						//check for death
						if(opponent.getCurrentHealth() <= 0){continue;};
			
						//opponent move
						player1->defend(opponent.attack(combatround));
					}
	
		
					//give stamina/mana allowances
					player1->replenish();
					opponent.replenish();

					combatround++;
				}else{
					printf("Battle over\n");
					if(player1->getCurrentHealth() <= 0){
						//gameover
					}
					//delete opponent

					//gamestate = 1;
				}
				

				//---render screen objects---
				//render battle scene

				//render character/enemy stats

				//render actions menu
				textures.attackTextTexture->render(240, 240);
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
	textures.gTileTexture->free();
	textures.attackTextTexture->free();

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

	textures.gTileTexture = new LTexture;
	if(textures.gTileTexture == NULL){
		printf("Failed to allocate gTileTexture!\n");
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

	//Load tile texture - replace with our tile sprite sheet
	if( !textures.gTileTexture->loadFromFile( "tileSpritesSizeChange.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	
	//open font
	gFont = TTF_OpenFont("Xerox Sans Serif Narrow.ttf", 20);
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
	}

	return success;
}
