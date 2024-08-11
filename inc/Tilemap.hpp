#pragma once

#include "core.hpp"
#include <sys/types.h>

#define NEW_MAP_SIZE 16

typedef enum tile_type_e
{
	TILE_EMPTY,
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_ROCK
}				tile_type_t;

typedef enum tile_dir_e
{
	NO,
	NE,
	EA,
	SE,
	SO,
	SW,
	WE,
	NW
}				tile_dir_t;

typedef enum grid_type_e
{
	GRID_DEF,
	GRID_ISO,
	GRID_HEX_X,
	GRID_HEX_Y
}				grid_type_t;


/* ================= Tile Struct ================= */


typedef struct tile_s
{
	uint	id;
	uiar2D	pos;
	bool	isPopulated;

	tile_type_t		type;
	struct tile_s	*nbrs[ 8 ];

}				tile_t;

typedef vector<vector<tile_t>>	tile_map_t;
typedef vector<tile_t>					tile_row_t;

void printTile( tile_t *tile );
void printFullTile( tile_t *tile );

bool areTilesNeighbors( tile_t *tile1, tile_t *tile2 );
void linkTiles( tile_t *tile1, tile_t *tile2 );
void linkToNeighbors( tile_t *tile, tile_map_t *map );

tile_type_t randomTileType();


/* ================ Tilemap Class ================ */


class Tilemap
{
	private:
		uint				size;
		uint				maxTileID;
		uiar2D				offset;
		grid_type_t	gridType;
		tile_map_t	map;

		Tilemap() = delete;
		void initMap();
		void clearMap();

	public:
		Tilemap( uint size, grid_type_t _gridType );
		~Tilemap();

		void populateMap();

		//tile_t *getTileFromID( uint id );
		tile_t *getTile( uint x, uint y );
		tile_t *setTile( uint x, uint y, tile_type_t _tileType );

		void setOffset( uint x, uint y );
		void setOffset( uiar2D offset );
		uiar2D getOffset();

		void iterOnTiles( void (*f)( tile_t* ));
		void printTileAt( uint x, uint y );
		void printMap();
};