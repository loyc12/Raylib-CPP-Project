#include "../../inc/Tilemap.hpp"

void printTile( t_tile *tile )
{
	switch ( tile->type )
	{
		case TILE_EMPTY:
			cout << "  ";
			break;
		case TILE_GRASS:
			cout << "//";
			break;
		case TILE_SAND:
			cout << "~~";
			break;
		case TILE_WATER:
			cout << "::'";
			break;
		case TILE_ROCK:
			cout << "XX";
			break;
	}
}

Tilemap::Tilemap( int _size, t_grid_type _gridType )
{
	this->size = _size;
	this->offset[ IX ] = 0; // TODO : center on init ( via map dimensions )
	this->offset[ IY ] = 0;
	this->gridType = _gridType;

	this->generateMap();
}

void Tilemap::generateMap()
{
	// Initiating the map
	for ( int y = 0; y < this->size; y++ )
	{
		vector<t_tile> newRow;

		for ( int x = 0; x < this->size; x++ )
		{
			t_tile newTile;

			newTile.id = ( y * this->size ) + x;
			newTile.mapX = x;
			newTile.mapY = y;
			newTile.type = TILE_EMPTY;

			newRow.push_back( newTile );
		}
		this->map.push_back( newRow );
	}

	// Setting the neighbors
	for ( int y = 0; y < this->size; y++ )
	{
		for ( int x = 0; x < this->size; x++ )
		{
			if ( y > 0 )
				this->map[y][x].north = &this->map[y - 1][x];
			if ( x > 0 )
				this->map[y][x].west  = &this->map[y][x - 1];
			if ( y < this->size - 1 )
				this->map[y][x].south = &this->map[y + 1][x];
			if ( x < this->size - 1 )
				this->map[y][x].east  = &this->map[y][x + 1];
		}
	}

}

Tilemap::~Tilemap()
{
	this->clearMap();
}

void Tilemap::clearMap()
{

}

void Tilemap::printTileAt( int x, int y ) { printTile( &this->map[y][x] ); }
void Tilemap::printMap()
{
	for ( int y = 0; y < this->size; y++ )
	{
		for ( int x = 0; x < this->size; x++ )
			printTile( &this->map[y][x] );
	}
}

t_tile *Tilemap::getTile( int x, int y ) { return &this->map[y][x]; }
t_tile *Tilemap::setTile( int x, int y, t_tile_type _tileType )
{
	this->map[y][x].type = _tileType;
	return &this->map[y][x];
}

void Tilemap::setOffset( int x, int y ) { this->offset = arr2{ x, y }; }
void Tilemap::setOffset( arr2 _offset ) { this->offset = _offset; }
arr2 Tilemap::getOffset() { return this->offset; }

void Tilemap::iterOnTiles( void ( *f )( t_tile* ))
{
	for ( int y = 0; y < this->size; y++ )
	{
		for ( int x = 0; x < this->size; x++ )
			f( &map[y][x] );
	}
}
