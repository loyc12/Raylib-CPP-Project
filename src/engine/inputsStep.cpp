#include "../../inc/Engine.hpp"


void Engine::inputsStep()
{
	DEBUG( "Here", "inputsStep" );
	this->deltaTime = GetFrameTime();

	if ( IsKeyPressed( KEY_ESCAPE ) )
		this->gameState = GAME_STOP;
	if ( IsKeyPressed( KEY_P ) )
		this->togglePause();

	{
		iar2D panDir = { 0, 0 };

		if ( IsKeyDown( KEY_W ) || IsKeyDown( KEY_UP ))			panDir[ IY ] = -MAP_PAN_SPEED;
		if ( IsKeyDown( KEY_S ) || IsKeyDown( KEY_DOWN ))		panDir[ IY ] =  MAP_PAN_SPEED;
		if ( IsKeyDown( KEY_A ) || IsKeyDown( KEY_LEFT ))		panDir[ IX ] = -MAP_PAN_SPEED;
		if ( IsKeyDown( KEY_D ) || IsKeyDown( KEY_RIGHT ))	panDir[ IX ] =  MAP_PAN_SPEED;

		if ( panDir[ IX ] != 0 || panDir[ IY ] != 0 )
			this->panMap( panDir );
	}

}