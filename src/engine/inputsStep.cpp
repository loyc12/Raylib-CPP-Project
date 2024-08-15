#include "../../inc/Engine.hpp"
#include "../../inc/inputs.hpp"


void Engine::inputsStep()
{
	DEBUG( "Here", "inputsStep" );

	this->deltaTime = GetFrameTime(); // updating deltaTime

	// hotkeys
	if ( IsKeyPressed( KEY_ESCAPE ) )
		this->gameState = GAME_STOP;
	if ( IsKeyPressed( KEY_P ) )
		this->togglePause();

	// camera stuff
	{
		iar2D panDir = { 0, 0 };

		if ( IsKeyDown( KEY_W ) || IsKeyDown( KEY_UP ))			panDir[ IY ] =  MAP_PAN_SPEED;
		if ( IsKeyDown( KEY_S ) || IsKeyDown( KEY_DOWN ))		panDir[ IY ] = -MAP_PAN_SPEED;
		if ( IsKeyDown( KEY_A ) || IsKeyDown( KEY_LEFT ))		panDir[ IX ] =  MAP_PAN_SPEED;
		if ( IsKeyDown( KEY_D ) || IsKeyDown( KEY_RIGHT ))	panDir[ IX ] = -MAP_PAN_SPEED;

		if ( IsKeyDown( KEY_LEFT_SHIFT ) || IsKeyDown( KEY_RIGHT_SHIFT ))
		{
			panDir[ IX ] *= SHIFT_COEF;
			panDir[ IY ] *= SHIFT_COEF;
		}
		if ( panDir[ IX ] != 0 || panDir[ IY ] != 0 )
			this->panMap( panDir );
	}

	// mouse stuff
	{
		uiar2D mousePos = { uint( GetMouseX() ), uint( GetMouseY() )};
		if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ))
		{
			DEBUG( "Mouse left button pressed", "inputsStep" );

			tile_t *tile = this->tilemap->getTileAt( mousePos );
			if ( tile )
				printFullTile( tile );
		}
		if ( IsMouseButtonPressed( MOUSE_RIGHT_BUTTON ))
		{
			DEBUG( "Mouse right button pressed", "inputsStep" );
		}

		// zoom with mouse wheel
		float zoom = 0;
		if ( GetMouseWheelMove() > 0 ) { zoom = MAP_ZOOM_SPEED; }
		if ( GetMouseWheelMove() < 0 ) { zoom = 1.0f / MAP_ZOOM_SPEED; }
		if ( IsKeyDown( KEY_LEFT_SHIFT ) || IsKeyDown( KEY_RIGHT_SHIFT ))
		{
			zoom *= zoom;
		}
		if ( zoom != 0 ) { this->tilemap->zoomMap( zoom ); }
	}

}