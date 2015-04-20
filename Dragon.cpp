//Dot.cpp Practice for the final project

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Dot.h"
#include "fsdmlevel.h"
#include "fsdmgame.h"
#include "winrend.h"


SDL_Rect gObject[1];

Object::Object()
{
    //Initialize the collision box
    mBox.x = 50;
    mBox.y = 50;
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

void Object::render( SDL_Rect& camera, LTexture* gObjectTexture)
{
    //Show the dot
	gObjectTexture->render( mBox.x - camera.x, mBox.y - camera.y, &gDragon[0] );
}

bool Object::touchesWall( SDL_Rect box, Tile* tiles[] )
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

bool Object::checkCollision( SDL_Rect a, SDL_Rect b )
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

bool Object::loadMedia()
{
	textures.gObjectTexture = new LTexture;
	if(textures.gObjectTexture == NULL){
		printf("Failed to allocate gDragonTexture!\n");
		success = false;
	}

	if( !textures.gObjectTexture->loadFromFile( "characters-2sizeChange.png" ) )
	{
		printf( "Failed to load object texture!\n" );
		success = false;
	}
	else
	{
		//Set bottom right sprite
		gRedMan[ 0 ].x = 100*2;
		gRedMan[ 0 ].y = 25*2;
		gRedMan[ 0 ].w = 25*2;
		gRedMan[ 0 ].h = 25*2;
	}
	return success;
}
