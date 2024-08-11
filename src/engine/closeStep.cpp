#include "../../inc/Engine.hpp"


void Engine::closeStep()
{
	INFO( "Closing game", "closeStep" );

	CloseWindow();

	delete tilemap;  tilemap = nullptr;
}