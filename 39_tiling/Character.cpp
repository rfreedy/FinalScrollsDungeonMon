//Dot.cpp Practice for the final project

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Dot.h"
#include "fsdmlevel.h"
#include "fsdmgame.h"
#include "winrend.h"

Dot::Dot()
{
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

void Dot::handleEvent( SDL_Event& e )
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

int Dot::getVely(){
	return mVelY;
}
int Dot::getVelx(){
	return mVelX;
}

void Dot::move( Tile *tiles[] )
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

void Dot::setCamera( SDL_Rect& camera )
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

void Dot::render( SDL_Rect& camera, LTexture* gDotTexture)
{
    //Show the dot
	gDotTexture->render( mBox.x - camera.x, mBox.y - camera.y, currentClip );
}

bool Dot::touchesWall( SDL_Rect box, Tile* tiles[] )
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

bool Dot::checkCollision( SDL_Rect a, SDL_Rect b )
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

/*
bool Dot::touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= TILE_CENTER ) && ( tiles[ i ]->getType() <= TILE_TOPLEFT ) )
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
*/