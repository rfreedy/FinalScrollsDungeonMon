//	fsdmrender.cpp		3/25/15	Kurt Davis
/*
 *	
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//screen size constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//texture wrapper
class LTexture{
	public:
		LTexture();	//constructor
		~LTexture();
		
		bool loadFromFile(std::string path);	//loads image from path
		void free();				//deallocate texture
		
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(Uint8 alpha);		

		void render(int x, int y, SDL_Rect* clip = NULL);		//render at point (x, y)

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;			//hardware texture

		int mWidth;				//image dimensions
		int mHeight;
};

//initialization and closing functions
bool init();
bool loadMedia();
void close();

//loading functions
SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gModulatedTexture;
LTexture gBackgroundTexture;

//constructor
LTexture::LTexture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

//deconstructor
LTexture::~LTexture(){
	free();		//deallocate
}

bool LTexture::loadFromFile(std::string path){
	
	free();		//deallocate

	//create surface, convert to texture, free surface

	SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL ){
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        }else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));		

        	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( newTexture == NULL ){
                        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }else{
			//assign dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

                SDL_FreeSurface( loadedSurface );
        }

        mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free(){
	if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	//modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::render(int x, int y, SDL_Rect* clip){
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if(clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth(){
	return mWidth;
}

int LTexture::getHeight(){
	return mHeight;
}

bool init(){
	bool success = true;
	
	//init SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}else{
		//linear texture filering
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( gWindow == NULL ){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}else{
			//create renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}else{
				//set renderer color (renderer, R, G, B, Alpha)
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//init PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(){
	bool success = true;

	//load textures
	if(!gModulatedTexture.loadFromFile("images/fadeout.png")){
		printf("Failed to load front texture!\n");
		success = false;
	}else{
		gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	if(!gBackgroundTexture.loadFromFile("images/fadein.png")){
		printf("Failed to load background texture!\n")
		success = false;
	}

	return success;
}

void close(){
	//free images
	gSpriteSheetTexture.free();	

	//destroy renderer and window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//quit SDL
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] ){
	//init SDL
	if( !init() ){
		printf( "Failed to initialize!\n" );
	}else{	
		//load images, textures
		if( !loadMedia() ){
			printf( "Failed to load media!\n" );
		}else{	
			bool quit = false;

			SDL_Event e;

			//game loop
			while(!quit){
				while(SDL_PollEvent( &e ) != 0){
					if(e.type == SDL_QUIT){
						quit = true;
					}
				}

				//clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear( gRenderer );

				//render screen				

				//redraw screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}
