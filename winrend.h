//Global variables are bad. However, this appears to be the only way to use the LTexture wrapper across multiple files.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Rect gRedMan[8];		//class for aninamted character
extern TTF_Font* gFont;
