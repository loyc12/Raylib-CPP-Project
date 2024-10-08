#pragma once

#include "core.hpp"
#include <sys/types.h>

#define MAP_PAN_SPEED 4
#define NEW_MAP_SIZE 128
//#define MAX_MAP_SIZE 512
#define MAP_ZOOM_SPEED 0.90f
#define NEW_TILE_SCALE 64
#define MIN_TILE_SCALE 16
#define MAX_TILE_SCALE 256
#define DEF_GRID_TYPE GRID_ISO
#define NO_MAP_TEXTURE false

typedef enum tile_type_e
{
	TILE_EMPTY,
	TILE_GRASS,
	TILE_SAND,
	TILE_DIRT,
	TILE_WATER,
	TILE_ROCK
}				tile_type_t;

typedef enum grid_type_e
{
	GRID_SQR,		// standard cartesian (square) grid
	GRID_ISO,		// isometric grid
	GRID_HEX_X,	// hexagonal grid with flat side on the top and bottom
	GRID_HEX_Y,	// hexagonal grid with flat side on the left and right
	GRID_TRI,		// triangular grid
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

// OBSOLETE
void drawTileDebug( tile_t *tile, uint tileScale, iar2D screenCoords, grid_type_t gridType );


/* ================ Tilemap Class ================ */


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

		// OBSOLETE
		void drawMapDebug();

		iar2D	getScreenCoords( uiar2D tileCoords );

		//tile_t *getTileFromID( uint id );
		tile_t *getTileAt( uiar2D screenCoords );
		tile_t *getTile( uint x, uint y );
		tile_t *setTile( uint x, uint y, tile_type_t _tileType );

		grid_type_t getGridType();
		uint getSize();

		uint getTileScale();
		void setTileScale( uint _tileScale );
		void zoomMap( float zoomFactor );

		iar2D	getOffset();
		void	setOffset( iar2D offset );
		void	modOffset( iar2D delta );

		bool isTileValid( uint x, uint y );
		void iterOnTiles( void (*f)( tile_t* ));
		void printTileAt( uint x, uint y );
		void printMap();
};