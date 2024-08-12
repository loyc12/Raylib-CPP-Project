#pragma once

#include "core.hpp"
#include <sys/types.h>


typedef enum tile_type_e
{
	TILE_EMPTY,
	TILE_GRASS,
	TILE_SAND,
	TILE_WATER,
	TILE_ROCK
}				tile_type_t;

typedef enum grid_type_e
{
	GRID_SQR,		// standard cartesian (square) grid
	GRID_ISO,		// isometric grid
	GRID_TRI,		// triangular grid
	GRID_HEX_X,	// hexagonal grid with flat side on the top and bottom
	GRID_HEX_Y,	// hexagonal grid with flat side on the left and right
}				grid_type_t;


typedef enum grid_dir_e { NO, NE, EA, SE, SO, SW, WE, NW } grid_dir_t;

/* ================= Tile Struct ================= */


typedef struct tile_s
{
	uint					id;
	uiar2D				pos;
	bool					isPopulated;
	tile_type_t		type;
	struct tile_s	*nbrs[ 8 ]; // neighboring tiles

}				tile_t;

typedef vector<vector<tile_t>>	tile_map_t;
typedef vector<tile_t>					tile_row_t;

tile_type_t randomTileType();

void printTile( tile_t *tile );
void printFullTile( tile_t *tile );

bool areTilesNeighbors( tile_t *tile1, tile_t *tile2 );
void linkTiles( tile_t *tile1, tile_t *tile2 );
void linkToNeighbors( tile_t *tile, tile_map_t *map );

void drawTile( tile_t *tile, uint tileScale, iar2D screenCoords, grid_type_t gridType );


/* ================ Tilemap Class ================ */


#define MAP_PAN_SPEED 3
#define NEW_MAP_SIZE 16
#define NEW_TILE_SCALE 64
#define MIN_TILE_SCALE 16
#define MAX_TILE_SCALE 512
#define DEF_GRID_TYPE GRID_ISO

class Tilemap
{
	private:
		uint				size;
		uint				tileScale;
		uint				maxTileID;
		iar2D				offset;
		grid_type_t	gridType;
		tile_map_t	map;

		Tilemap() = delete;
		void initMap();
		void clearMap();

	public:
		Tilemap( uint size, grid_type_t _gridType );
		~Tilemap();

		void populateMap();
		void drawMap();

		iar2D	getScreenCoords( uiar2D tileCoords );

		//tile_t *getTileFromID( uint id );
		tile_t *getTileAt( uiar2D screenCoords );
		tile_t *getTile( uint x, uint y );
		tile_t *setTile( uint x, uint y, tile_type_t _tileType );

		uint getZoom();
		void setZoom( uint _tileScale );

		iar2D	getOffset();
		void	setOffset( iar2D offset );
		void	modOffset( iar2D delta );

		bool isTileValid( uint x, uint y );
		void iterOnTiles( void (*f)( tile_t* ));
		void printTileAt( uint x, uint y );
		void printMap();
};