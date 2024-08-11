#include "../inc/deps.hpp"
#include "../inc/ball.hpp"
#include "../inc/Tilemap.hpp"
#include <iostream>

//===========================================================//
//                           STEPS                           //
//===========================================================//

void inputsStep( Ball *ball )
{
	if ( ball != nullptr )
		ball->UpdateInputs();
	else
		WARN( "ball pointer needed", "main:inputsStep" );
}

void scriptsStep( Ball *ball )
{
	if ( ball != nullptr )
		ball->UpdateScripts();
	else
		WARN( "ball pointer needed", "main:scriptsStep" );
}

void physicsStep( Ball *ball )
{
	if ( ball != nullptr )
		ball->UpdatePhysics();
	else
		WARN( "ball pointer needed", "main:physicsStep" );
}

void graphicsStep( Ball *ball )
{
	static Color bgColor = Color{ 20, 40, 60, 255 };

	BeginDrawing();
	{
		ClearBackground( bgColor );

		if ( ball != nullptr )
			ball->UpdateGraphics(); // IDEA : split update and draw methods
	}
	EndDrawing();
}

//===========================================================//
//                        INIT && CLOSE                      //
//===========================================================//

void initStep( const char* title)
{
	const int screenWidth = 1024;
	const int screenHeight = 720;
	const int targetFPS = 60;

	InitWindow( screenWidth, screenHeight, title );
	SetTargetFPS( targetFPS );

	graphicsStep( nullptr );
}

void closeStep()
{
	CloseWindow();
}

//===========================================================//
//                         CORE LOOP                         //
//===========================================================//

void gameLoop( Ball *ball )
{
	while ( !WindowShouldClose() )
	{
		inputsStep( ball );
		scriptsStep( ball );
		physicsStep( ball );
		graphicsStep( ball );
	}
}

void testTilemap()
{
	cout << "testing Tilemap" << endl << endl;

	Tilemap map( 20, GRID_DEF );
	map.populateMap();
	map.printMap();
	printFullTile( map.getTile( 7, 7 ) );
}

int main()
{
	Ball ball;

	initStep("les get dis bish ruhnin" );
	{
		gameLoop( &ball );
	}
	closeStep();

	testTilemap();
}