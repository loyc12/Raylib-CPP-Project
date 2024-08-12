#include "../../inc/Engine.hpp"


Engine::Engine( const str _gameTitle, uint _screenWidth, uint _screenHeight, uint _targetFPS ) :
	gameTitle( _gameTitle ), screenWidth( _screenWidth ), screenHeight( _screenHeight ), targetFPS( _targetFPS ),
	isRunning( true ), deltaTime( 0.0 ), tilemap( nullptr ), gameState( GAME_INIT )
{
	this->initStep();
}

void Engine::togglePause()
{
	DEBUG( "Here", "togglePause" );

	if ( this->gameState != GAME_PAUSE && this->gameState != GAME_RUN )
	{
		sstream ss;
		ss << "Cannot pause game from current state: " << this->gameState;
		WARN( ss.c_str(), "togglePause" );
		return;
	}

	if ( this->isRunning)
		this->gameState = GAME_PAUSE;
	else
		this->gameState = GAME_RESUME;
}

void Engine::pauseStep()
{
	INFO( "Pausing game", "pauseStep" );
	this->isRunning = false;
	this->gameState = GAME_PAUSE;
}

void Engine::resumeStep()
{
	INFO( "Resuming game", "resumeStep" );
	this->isRunning = true;
	this->gameState = GAME_RUN;
}

void Engine::panMap( iar2D panDir )
{
	DEBUG( "Paning...", "panMap" );

	if ( this->gameState != GAME_RUN )
	{
		WARN( "Cannot pan map from current game state", "panMap" );
		return;
	}

	this->tilemap->modOffset( panDir );
}