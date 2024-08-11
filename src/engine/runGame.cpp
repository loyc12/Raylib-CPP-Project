#include "../../inc/Engine.hpp"


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
				return;

			case GAME_RUN:
			{
				DEBUG( "Begining a game loop...", "runGame" );
				this->inputsStep();
				this->scriptsStep();
				this->physicsStep();
				this->graphicsStep();
				this->drawingStep();
			}	break;

			case GAME_PAUSE:
			{
				DEBUG( "Attempting to pause game", "runGame" );
				if ( this->isRunning )
					this->pauseStep();
				else
				{
					this->inputsStep();
					this->drawingStep();
				}
			}	break;

			case GAME_RESUME:
			{
				DEBUG( "Attempting to resume game", "runGame" );
				if ( !this->isRunning )
					this->resumeStep();
			}	break;

			case GAME_STOP:
				INFO( "Stopping game", "runGame" );
				return;
		}
	}
}