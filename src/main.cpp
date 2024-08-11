#include "../inc/core.hpp"
#include "../inc/Engine.hpp"

void testTilemap()
{
	cout << "testing Tilemap" << endl << endl;

	Tilemap map( 20, GRID_SQR );
	map.populateMap();
	map.printMap();
	printFullTile( map.getTile( 7, 7 ) );
}

int main()
{
	Engine engine( "Testgame", 1024, 720, 60 );

	engine.runGame();
}