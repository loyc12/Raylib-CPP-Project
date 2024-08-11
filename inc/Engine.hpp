#pragma once

#include "core.hpp"
#include "Tilemap.hpp"

#define BKGRND_COLOR	CLITERAL( Color ) { 63, 63, 63, 255 }

typedef enum e_game_state
{
	GAME_INIT,
	GAME_RUN,
	GAME_PAUSE,
	GAME_RESUME,
	GAME_STOP
}				t_game_state;


/* ================ Engine Class ================ */


class Engine
{
	private:
		str			gameTitle;
		uint		screenWidth;
		uint		screenHeight;
		uint		targetFPS;
		bool		isRunning;
		double	deltaTime;
		Tilemap *tilemap;

		t_game_state	gameState;

		Engine() = delete;

		void inputsStep();
		void scriptsStep();
		void physicsStep();
		void graphicsStep();
		void drawingStep();

		void initStep();
		void closeStep();

		void togglePause();
		void pauseStep();
		void resumeStep();

		void panMap( iar2D panDir );

	public:
		Engine( const str _gameTitle, uint _screenWidth, uint _screenHeight, uint _targetFPS );
		~Engine();

		void runGame();

};