#include "../../inc/Engine.hpp"


void Engine::graphicsStep()
{
	DEBUG( "Here", "graphicsStep" );

}

void Engine::drawingStep()
{
	DEBUG( "Here", "drawingStep" );
	BeginDrawing();
	ClearBackground( BKGRND_COLOR );

	this->tilemap->drawMap();

	EndDrawing();
}