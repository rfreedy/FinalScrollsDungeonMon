//Matthew Perez
//CSE20212
//Final Project
//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

//simple animation accross screen
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 8;		//num of frames (pics)
SDL_Rect gRedMan[ WALKING_ANIMATION_FRAMES ];		//class for aninamted character
LTexture gSpriteSheetTexture;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
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
			//Create vsynced renderer for window
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
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "characters.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set top left sprite		FRONT
		gRedMan[ 0 ].x =   10;
		gRedMan[ 0 ].y =   0;
		gRedMan[ 0 ].w = 50;
		gRedMan[ 0 ].h = 50;

		//Set top right sprite
		gRedMan[ 1 ].x = 70;
		gRedMan[ 1 ].y =   0;
		gRedMan[ 1 ].w = 50;
		gRedMan[ 1 ].h = 50;
		
		//Set bottom left sprite	BACK
		gRedMan[ 2 ].x =   10;
		gRedMan[ 2 ].y = 50;
		gRedMan[ 2 ].w = 50;
		gRedMan[ 2 ].h = 50;

		//Set bottom right sprite
		gRedMan[ 3 ].x = 70;
		gRedMan[ 3 ].y = 50;
		gRedMan[ 3 ].w = 50;
		gRedMan[ 3 ].h = 50;

		//Set bottom left sprite	RIGHT
		gRedMan[ 4 ].x =   10;
		gRedMan[ 4 ].y = 100;
		gRedMan[ 4 ].w = 50;
		gRedMan[ 4 ].h = 50;

		//Set bottom right sprite
		gRedMan[ 5 ].x = 70;
		gRedMan[ 5 ].y = 100;
		gRedMan[ 5 ].w = 50;
		gRedMan[ 5 ].h = 50;

		//Set bottom left sprite	LEFT
		gRedMan[ 6 ].x =   10;
		gRedMan[ 6 ].y = 150;
		gRedMan[ 6 ].w = 50;
		gRedMan[ 6 ].h = 50;

		//Set bottom right sprite
		gRedMan[ 7 ].x = 70;
		gRedMan[ 7 ].y = 150;
		gRedMan[ 7 ].w = 50;
		gRedMan[ 7 ].h = 50;
	}
	
	return success;
}

void close()
{
	//Free loaded images
	gSpriteSheetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame = 0;
			SDL_Rect* currentClip;
			//While application is running
			int count = 0;
			int posX = 200;
			int posY = 200;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
					{
						//Clear screen
						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
						SDL_RenderClear( gRenderer );

						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_DOWN:
								//printf( "up \n");
								posY = posY +10;
								if(count%2 == 0){
									currentClip = &gRedMan[ 0 ];
								}
								else{
									currentClip = &gRedMan[ 1 ];
								}
								gSpriteSheetTexture.render( posX, posY, currentClip );
								count++;
							break;

							case SDLK_UP:
								posY = posY -10;
								if(count%2 == 0){
									currentClip = &gRedMan[ 2 ];
								}
								else{
									currentClip = &gRedMan[ 3 ];
								}
								gSpriteSheetTexture.render( posX, posY, currentClip );
								count++;
							break;

							case SDLK_RIGHT:
								posX = posX +10;
								if(count%2 == 0){
									currentClip = &gRedMan[ 4 ];
								}
								else{
									currentClip = &gRedMan[ 5 ];
								}
								gSpriteSheetTexture.render( posX, posY, currentClip );
								count++;
							break;

							case SDLK_LEFT:
								posX = posX -10;
								if(count%2 == 0){
									currentClip = &gRedMan[ 6 ];
								}
								else{
									currentClip = &gRedMan[ 7 ];
								}
								gSpriteSheetTexture.render( posX, posY, currentClip );
								count++;
							break;

							case SDLK_r:
								
							break;

							default:
								
							break;
						}
					}
				}

				//Update screen
				SDL_RenderPresent( gRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
