#include "../inc/core.hpp"
#include "../inc/Tilemap.hpp"


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
	testTilemap();
}