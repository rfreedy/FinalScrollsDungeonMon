/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
//keyboard
#include<SDL2/SDL.h>
#include <stdio.h>
#include<string>
#include <iostream>
using namespace std;

//Key press surfaces constants 
enum KeyPressSurfaces { 
	KEY_PRESS_SURFACE_DEFAULT, 
	KEY_PRESS_SURFACE_UP, 
	KEY_PRESS_SURFACE_DOWN, 
	KEY_PRESS_SURFACE_LEFT, 
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_R, 
	KEY_PRESS_SURFACE_TOTAL 
};

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//function initialization
bool init();
bool loadMedia();
void close();

	SDL_Surface* loadSurface(string path);

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	
	//global variables
	SDL_Surface* gScreenSurface = NULL;

	//image corresponding to key press
	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	//current image displayed
	SDL_Surface* gCurrentSurface = NULL;

	SDL_Surface* gXOut = NULL;

SDL_Surface* loadSurface(string path){
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface ==NULL){
		printf("no load\n", path.c_str(), SDL_GetError());
	}
	return loadedSurface;
}

bool init() { 
	//Initialization flag 
	bool success = true; 

	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		success = false; 
	} 
	else { 
		//Create window 
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
		if( gWindow == NULL ) { 
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
			success = false; 
		} 
		else { //Get window surface 
			gScreenSurface = SDL_GetWindowSurface( gWindow ); //grab surface contained by window
		} 
	} 
	return success; 
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "04_key_presses/press.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "04_key_presses/up.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load up image!\n" );
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "04_key_presses/down.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load down image!\n" );
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "04_key_presses/left.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "04_key_presses/right.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

	return success;
}


void close() { 
	//Deallocate surface 
	SDL_FreeSurface( gXOut ); 
	gXOut = NULL;

	 //Destroy window 
	SDL_DestroyWindow( gWindow ); 
	gWindow = NULL; 
	
	//Quit SDL subsystems 
	SDL_Quit(); 
}

int main( int argc, char* args[] )
{
	int up=0;		//counters to keep track of movement
	int down=0;
	int right=0;
	int left=0;
	if (!init())
		printf("failed to init\n");
	else{
		if(!loadMedia())
			printf("failed media\n");
		else{
			//main loop flag
			bool quit = false;
			SDL_Event e;		//action (ie keyboard stroke)
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while (!quit){	//x out functionality
				while(SDL_PollEvent(&e)!=0){
					if(e.type==SDL_QUIT){
						quit = true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
								gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
								up++;
							break;

							case SDLK_DOWN:
								gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
								down++;
							break;

							case SDLK_LEFT:
								gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
								left++;
							break;

							case SDLK_RIGHT:
								gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
								right++;
							break;

							case SDLK_r:
								up =0;
								down=0;
								right =0;
								left =0;
							break;

							default:
								gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}
				SDL_BlitSurface(gCurrentSurface,NULL,gScreenSurface, NULL); //1 = source image, 3 = destination
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}
	cout<<"up: "<<up<<endl;
	cout<<"down: "<<down<<endl;
	cout<<"left: "<<left<<endl;
	cout<<"right: "<<right<<endl;
	close();
	return 0;
}
