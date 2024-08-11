#pragma once

#include "deps.hpp"

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
	PRO_DEF,
	PRO_ISO,
	PRO_HEX_HOR,
	PRO_HEX_VER
}				t_grid_type;


typedef struct s_tile
{
	int id;
	int mapX;
	int mapY;
	t_tile_type		type;

	struct s_tile	*north;
	struct s_tile	*west;
	struct s_tile	*south;
	struct s_tile	*east;

}				t_tile;

#define t_tile_map vector<vector<t_tile>>
#define t_tile_row vector<t_tile>

void printTile( t_tile *tile );

class Tilemap
{
	private:
		int					size;
		arr2				offset;
		t_grid_type	gridType;
		t_tile_map	map;

		Tilemap();
		void generateMap();
		void clearMap();

	public:
		Tilemap( int size, t_grid_type _gridType );
		~Tilemap();

		void printTileAt( int x, int y );
		void printMap();

		t_tile *getTile( int x, int y );
		t_tile *setTile( int x, int y, t_tile_type _tileType );

		void setOffset( int x, int y );
		void setOffset( arr2 offset );
		arr2 getOffset();

		void iterOnTiles( void (*f)( t_tile* ));
};