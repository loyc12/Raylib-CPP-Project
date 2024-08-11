#include "../../inc/Engine.hpp"


Engine::~Engine() { closeStep(); }

void Engine::initStep()
{
	INFO( "Initializing game", "initStep" );

	InitWindow( this->screenWidth, this->screenHeight, this->gameTitle.c_str() );
	SetTargetFPS( targetFPS );

	this->tilemap = new Tilemap( NEW_MAP_SIZE, DEF_GRID_TYPE );
	this->tilemap->populateMap();

	this->gameState = GAME_RUN;
}