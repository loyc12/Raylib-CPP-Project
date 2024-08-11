#include "../inc/core.hpp"
#include "../inc/Engine.hpp"

int main()
{
	Engine engine( "Testgame", 1024, 1024, 60 );

	engine.runGame();
}