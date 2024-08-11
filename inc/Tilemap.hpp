#pragma once

#include "deps.hpp"
#include <sys/types.h>

typedef enum e_tile_type
{
	TILE_EMPTY,
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_ROCK
}				t_tile_type;

typedef enum e_grid_type
{
	GRID_DEF,
	GRID_ISO,
	GRID_HEX_X,
	GRID_HEX_Y
}				t_grid_type;

typedef struct s_tile
{
	uint	id;
	arr2	pos;
	bool	isPopulated;

	t_tile_type		type;
	struct s_tile	*no;
	struct s_tile	*ne;
	struct s_tile	*ea;
	struct s_tile	*se;
	struct s_tile	*so;
	struct s_tile	*sw;
	struct s_tile	*we;
	struct s_tile	*nw;

}				t_tile;

#define t_tile_map vector<vector<t_tile>>
#define t_tile_row vector<t_tile>

void printTile( t_tile *tile );
void printFullTile( t_tile *tile );
bool areTilesNeighbors( t_tile *tile1, t_tile *tile2 );
void linkTiles( t_tile *tile1, t_tile *tile2 );
t_tile_type randomTileType();

class Tilemap
{
	private:
		uint				size;
		uint				maxTileID;
		arr2				offset;
		t_grid_type	gridType;
		t_tile_map	map;

		Tilemap();
		void initMap();
		void clearMap();

	public:
		Tilemap( uint size, t_grid_type _gridType );
		~Tilemap();

		void populateMap();

		//t_tile *getTileFromID( uint id );
		t_tile *getTile( uint x, uint y );
		t_tile *setTile( uint x, uint y, t_tile_type _tileType );

		void setOffset( uint x, uint y );
		void setOffset( arr2 offset );
		arr2 getOffset();

		void iterOnTiles( void (*f)( t_tile* ));
		void printTileAt( uint x, uint y );
		void printMap();
};