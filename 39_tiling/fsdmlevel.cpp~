//Final Project		fsdmlevel.cpp	4/11/15		Author: Kurt Davis
//Level Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "fsdmlevel.h"
#include "winrend.h"

FSDMLevel::FSDMLevel() {
	
	construct_success = true;

	//Load tile map
	if( !setTiles() )
	{
		printf( "Failed to load tile set!\n" );
		construct_success = false;
	}
}

FSDMLevel::~FSDMLevel() {

}

void FSDMLevel::free(){
	//Deallocate tileSet
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( !(tileSet[ i ] == NULL) )
		 {
			delete tileSet[ i ];
			tileSet[ i ] = NULL;
		 }
	}
	return;
}

void FSDMLevel::render( SDL_Rect& camera, LTexture* gTileTexture){	
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		tileSet[ i ]->render( camera, getTileClip(tileSet[i]->getType()), gTileTexture);
	}
}

bool FSDMLevel::constructed(){
	return construct_success;
}

Tile** FSDMLevel::getTileSet(){
	return tileSet;
}

//return pointer to element of gTileClips as per tile::render
SDL_Rect* FSDMLevel::getTileClip(int mtype){
	return &(gTileClips[mtype]);
}

bool FSDMLevel::setTiles()
{
	//Success flag
	bool tilesLoaded = true;

    	//The tile offsets
    	int x = 0, y = 0;

    	//Open the map
    	std::ifstream map( "lazy.map" );

    	//If the map couldn't be loaded
    	if( map == NULL )
    	{
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    	}else{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tileSet[ i ] = new Tile( x, y, tileType );
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_GRASS ].x = 0;
			gTileClips[ TILE_GRASS ].y = 160*2;
			gTileClips[ TILE_GRASS ].w = TILE_WIDTH;
			gTileClips[ TILE_GRASS ].h = TILE_HEIGHT;

			gTileClips[ TILE_DIRT ].x = 176*2;
			gTileClips[ TILE_DIRT ].y = 16*2;
			gTileClips[ TILE_DIRT ].w = TILE_WIDTH;
			gTileClips[ TILE_DIRT ].h = TILE_HEIGHT;

			gTileClips[ TILE_DUNGEON ].x = 304*2;
			gTileClips[ TILE_DUNGEON ].y = 128*2;
			gTileClips[ TILE_DUNGEON ].w = TILE_WIDTH;
			gTileClips[ TILE_DUNGEON ].h = TILE_HEIGHT;

			gTileClips[ TILE_WATER ].x = 64*2;
			gTileClips[ TILE_WATER ].y = 0;
			gTileClips[ TILE_WATER ].w = TILE_WIDTH;
			gTileClips[ TILE_WATER ].h = TILE_HEIGHT;

			gTileClips[ TILE_TREES ].x = 224*2;
			gTileClips[ TILE_TREES ].y = 0;
			gTileClips[ TILE_TREES ].w = TILE_WIDTH;
			gTileClips[ TILE_TREES ].h = TILE_HEIGHT;

			gTileClips[ TILE_MOUNTAINS ].x = 48*2;
			gTileClips[ TILE_MOUNTAINS ].y = 160*2;
			gTileClips[ TILE_MOUNTAINS ].w = TILE_WIDTH;
			gTileClips[ TILE_MOUNTAINS ].h = TILE_HEIGHT;

			gTileClips[ TILE_LAVA ].x = 128*2;
			gTileClips[ TILE_LAVA ].y = 0;
			gTileClips[ TILE_LAVA ].w = TILE_WIDTH;
			gTileClips[ TILE_LAVA ].h = TILE_HEIGHT;

			gTileClips[ TILE_SKINNYTREES ].x = 176*2;
			gTileClips[ TILE_SKINNYTREES ].y = 160*2;
			gTileClips[ TILE_SKINNYTREES ].w = TILE_WIDTH;
			gTileClips[ TILE_SKINNYTREES ].h = TILE_HEIGHT;

			gTileClips[ TILE_BRICKS ].x = 176*2;
			gTileClips[ TILE_BRICKS ].y = 112*2;
			gTileClips[ TILE_BRICKS ].w = TILE_WIDTH;
			gTileClips[ TILE_BRICKS ].h = TILE_HEIGHT;

			gTileClips[ TILE_SANDWALL ].x = 240*2;
			gTileClips[ TILE_SANDWALL ].y = 0;
			gTileClips[ TILE_SANDWALL ].w = TILE_WIDTH;
			gTileClips[ TILE_SANDWALL ].h = TILE_HEIGHT;

			gTileClips[ TILE_WATERFALL ].x = 64*2;
			gTileClips[ TILE_WATERFALL ].y = 96*2;
			gTileClips[ TILE_WATERFALL ].w = TILE_WIDTH;
			gTileClips[ TILE_WATERFALL ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOULDERS ].x = 272*2;
			gTileClips[ TILE_BOULDERS ].y = 160*2;
			gTileClips[ TILE_BOULDERS ].w = TILE_WIDTH;
			gTileClips[ TILE_BOULDERS ].h = TILE_HEIGHT;
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}
