//Final Project		fsdmlevel.cpp	4/11/15		Author: Kurt Davis
//Level Instance for FSDM game, interface file
//Lines commented #DEBUG# are for debugging and should be commented out for final release

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

#include "fsdmlevel.h"
#include "winrend.h"

FSDMLevel::FSDMLevel(int map) {
	
	construct_success = true;

	//Load tile map
	if( !setTiles(map) )
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

bool FSDMLevel::setTiles(int maplevel)
{
	std::cout << "test" << std::endl;
	//Success flag
	bool tilesLoaded = true;

    	//The tile offsets
    	int x = 0, y = 0;
	// map names 
	std::string overworld = "overworld.map";
	std::string dungeon1 = "dungeon4.map";
	std::string dungeon2 = "dungeon3.map";
	//declare map variable
	std::ifstream map; 
	std::cout << "map level value: " << maplevel << std::endl;
    	//Open the map
    	switch(maplevel) {
		case OVERWORLD: { 
			map.open( overworld.c_str(), std::ifstream::in );
			break;
			}
		case DUNGEON1: {
			 map.open( dungeon1.c_str(), std::ifstream::in );
			break;
			}
		case DUNGEON2: {
			 map.open( dungeon2.c_str(), std::ifstream::in );
			break;
			}	
	}
    	//If the map couldn't be loaded
    	if( map == NULL )
    	{
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    	}else{
		std::cout << "total tiles is: " << TOTAL_TILES << std::endl;
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
	//		std::cout << "x= " << x << std::endl;
			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
	//		std::cout << "y= " << y << std::endl;
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{	
			//std::cout << "tiles loaded successfully" << std::endl;
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

			gTileClips[ TILE_WATER ].x = 32;
			gTileClips[ TILE_WATER ].y = 32*5;
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

			gTileClips[ TILE_LAVA ].x = 32;
			gTileClips[ TILE_LAVA ].y = 32*7;
			gTileClips[ TILE_LAVA ].w = TILE_WIDTH;
			gTileClips[ TILE_LAVA ].h = TILE_HEIGHT;

			gTileClips[ TILE_SKINNYTREES ].x = 32*11;
			gTileClips[ TILE_SKINNYTREES ].y = 32*10;
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

			gTileClips[ TILE_SNOW ].x = 32*13;
			gTileClips[ TILE_SNOW ].y = 32*9;
			gTileClips[ TILE_SNOW ].w = TILE_WIDTH;
			gTileClips[ TILE_SNOW ].h = TILE_HEIGHT;
	
			gTileClips[ TILE_SNOW_TREES ].x = 32*12;
			gTileClips[ TILE_SNOW_TREES ].y = 32*9;
			gTileClips[ TILE_SNOW_TREES ].w = TILE_WIDTH;
			gTileClips[ TILE_SNOW_TREES ].h = TILE_HEIGHT;

			gTileClips[ TILE_SNOW_MOUNTAINS ].x = 32*15;
			gTileClips[ TILE_SNOW_MOUNTAINS ].y = 32*9;
			gTileClips[ TILE_SNOW_MOUNTAINS ].w = TILE_WIDTH;
			gTileClips[ TILE_SNOW_MOUNTAINS ].h = TILE_HEIGHT;

			gTileClips[ TILE_STAIR_1 ].x = 32*15;
			gTileClips[ TILE_STAIR_1 ].y = 32*15;
			gTileClips[ TILE_STAIR_1 ].w = TILE_WIDTH;
			gTileClips[ TILE_STAIR_1 ].h = TILE_HEIGHT;

			gTileClips[ TILE_BRICKS_WALKING].x = 32*15;
                        gTileClips[ TILE_BRICKS_WALKING ].y = 32*4;
                        gTileClips[ TILE_BRICKS_WALKING].w = TILE_WIDTH;
                        gTileClips[ TILE_BRICKS_WALKING ].h = TILE_HEIGHT;

                        gTileClips[ TILE_LAVA_BRIDGE ].x = 32*17;
                        gTileClips[ TILE_LAVA_BRIDGE ].y = 32*15;
                        gTileClips[ TILE_LAVA_BRIDGE].w = TILE_WIDTH;
                        gTileClips[ TILE_LAVA_BRIDGE].h = TILE_HEIGHT;
			
			gTileClips[ TILE_STAIR_UP ].x = 32*14;
			gTileClips[ TILE_STAIR_UP ].y = 32*15;
			gTileClips[ TILE_STAIR_UP ].w = TILE_WIDTH;
			gTileClips[ TILE_STAIR_UP ].h = TILE_HEIGHT;



					}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}
