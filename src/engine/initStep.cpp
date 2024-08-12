#include "../../inc/Engine.hpp"
#include <cstdlib>
#include <raylib.h>


Engine::~Engine() { closeStep(); }

void Engine::initStep()
{
	INFO( "Initializing game", "initStep" );

	InitWindow( this->screenWidth, this->screenHeight, this->gameTitle.c_str() );
	SetTargetFPS( targetFPS );

	this->tilemap = new Tilemap( NEW_MAP_SIZE, DEF_GRID_TYPE );
	this->tilemap->populateMap();

	this->loadImages();

	this->gameState = GAME_RUN;
}

void Engine::loadImages()
{
	INFO( "Loading images", "loadImages" );

	this->tileAtlas = LoadTexture( "/home/loyc/Desktop/Raylib-CPP-Project/assets/textures/tileAtlas.png" );

	if ( this->tileAtlas.id == 0 )
	{
		ERROR( "Failed to load tileAtlas", "loadImages" );
		Engine::closeStep();
		exit( EXIT_FAILURE );
	}
}