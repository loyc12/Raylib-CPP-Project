#include "../inc/deps.hpp"
#include "../inc/ball.hpp"


void inputsStep( Ball *ball )
{
	if ( ball != nullptr )
		ball->UpdateInputs();
	else
		cerr << "error : inputsStep() : ball pointer needed" << endl;
}

void scriptsStep( Ball *ball )
{
	if ( ball != nullptr )
		ball->UpdateScripts();
	else
		cerr << "error : scriptsStep() : ball pointer needed" << endl;
}

void physicsStep( Ball *ball )
{
	if ( ball != nullptr )
		ball->UpdatePhysics();
	else
		cerr << "error : physicsStep() : ball pointer needed" << endl;
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

void initStep( const char* title)
{
	const int screenWidth =		1024;
	const int screenHeight =	720;
	const int targetFPS = 		60;

	InitWindow( screenWidth, screenHeight, title );
	SetTargetFPS( targetFPS );

	graphicsStep( nullptr );
}

void gameLoop()
{
	Ball ball = Ball();

	while ( !WindowShouldClose() )
	{
		inputsStep( &ball );
		scriptsStep( &ball );
		physicsStep( &ball );
		graphicsStep( &ball );
	}
}

void closeStep()
{
	CloseWindow();
}

int main()
{
	initStep("les get dis bish ruhnin" );
	{
		gameLoop();
	}
	closeStep();
}