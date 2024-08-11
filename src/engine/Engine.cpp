#include "../../inc/Engine.hpp"

void Engine::inputsStep()
{
	DEBUG( "Here", "inputsStep" );
	this->deltaTime = GetFrameTime();

	if ( IsKeyPressed( KEY_P ) )
		this->togglePause();

}

void Engine::scriptsStep()
{
	DEBUG( "Here", "scriptsStep" );

}

void Engine::physicsStep()
{
	DEBUG( "Here", "physicsStep" );

}

void Engine::graphicsStep()
{
	DEBUG( "Here", "graphicsStep" );

}

void Engine::drawingStep()
{
	DEBUG( "Here", "drawingStep" );
	BeginDrawing();
	ClearBackground( BKGRND_COLOR );

	//this->tilemap->drawMap();

	EndDrawing();
}

Engine::Engine( const str _gameTitle, uint _screenWidth, uint _screenHeight, uint _targetFPS ) :
	gameTitle( _gameTitle ), screenWidth( _screenWidth ), screenHeight( _screenHeight ), targetFPS( _targetFPS ),
	isRunning( true ), deltaTime( 0.0 ), tilemap( nullptr ), gameState( GAME_INIT )
{
	this->initStep();
}

Engine::~Engine() { closeStep(); }

void Engine::initStep()
{
	INFO( "Initializing game", "initStep" );

	InitWindow( this->screenWidth, this->screenHeight, this->gameTitle.c_str() );
	SetTargetFPS( targetFPS );

	this->tilemap = new Tilemap( NEW_MAP_SIZE, GRID_DEF );
	this->tilemap->populateMap();

	this->gameState = GAME_RUN;
}

void Engine::closeStep()
{
	INFO( "Closing game", "closeStep" );

	CloseWindow();
	delete tilemap;
}

void Engine::togglePause()
{
	INFO( "Pausing / Unpausing", "togglePause" );

	if ( this->gameState != GAME_PAUSE && this->gameState != GAME_RUN )
	{
		sstream ss;
		ss << "Cannot pause game from current state: " << this->gameState;
		WARN( ss.str().c_str(), "togglePause" );
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

void Engine::runGame()
{
	INFO( "Running game", "runGame" );
	while ( true)
	{
		if ( WindowShouldClose() )
			this->gameState = GAME_STOP;

		switch ( this->gameState )
		{
			case GAME_INIT:
				WARN( "Cannot run an uninitialzed game", "runGame" );
				break;

			case GAME_RUN:
			{
				this->inputsStep();
				this->scriptsStep();
				this->physicsStep();
				this->graphicsStep();
				this->drawingStep();
			}	break;

			case GAME_PAUSE:
			{
				if ( this->isRunning )
					this->pauseStep();
				else
					this->inputsStep();
			}	break;

			case GAME_RESUME:
			{
				if ( !this->isRunning )
					this->resumeStep();
			}	break;

			case GAME_STOP:
				this->closeStep();
				exit( 0 );
		}
	}
}