//Global variables are bad. However, this appears to be the only way to use the LTexture wrapper across multiple files.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Rect gRedMan[8];		//class for aninamted character
//extern TTF_Font* gFont;
extern SDL_Rect gDragon[1];
extern SDL_Rect gBoss[1];	//need to be implemented
//for enemies: add SDL_Rect in winrend, Ltexture in fsdmgame.h, and picture in fsdmgame.cpp
