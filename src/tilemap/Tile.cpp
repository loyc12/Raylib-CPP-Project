#include "../../inc/Tilemap.hpp"


tile_type_t randomTileType()
{
	tile_type_t tileType = TILE_EMPTY;

	byte r = rand() % 5;
	switch ( r )
	{
		case 0:
			tileType = TILE_GRASS;
			break;
		case 1:
			tileType = TILE_DIRT;
			break;
		case 2:
			tileType = TILE_SAND;
			break;
		case 3:
			tileType = TILE_WATER;
			break;
		case 4:
			tileType = TILE_ROCK;
			break;
	}
	// TODO : change tileType based on neighbours here

	return tileType;
}


void printTile( tile_t *tile )
{
	switch ( tile->type )
	{
		case TILE_EMPTY:
			cout << "  ";
			break;
		case TILE_GRASS:
			cout << "//";
			break;
		case TILE_DIRT:
			cout << "[]";
			break;
		case TILE_SAND:
			cout << "~~";
			break;
		case TILE_WATER:
			cout << "::";
			break;
		case TILE_ROCK:
			cout << "XX";
			break;
	}
}

void printFullTile( tile_t *tile )
{
	cout << "Tile #" << tile->id << " at [ " << tile->pos[ IX ] << ":" << tile->pos[ IY ] << " ]" << endl;
	cout << "Type : ";
	printTile( tile );
	cout << endl << "Neighbors :" << endl;

	if ( tile->nbrs[ NO ] != nullptr )
		cout << "NO : Tile #" << tile->nbrs[ NO ]->id << " at [ " << tile->nbrs[ NO ]->pos[ IX ] << ":" << tile->nbrs[ NO ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ NE ] != nullptr )
		cout << "NE : Tile #" << tile->nbrs[ NE ]->id << " at [ " << tile->nbrs[ NE ]->pos[ IX ] << ":" << tile->nbrs[ NE ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ EA ] != nullptr )
		cout << "EA : Tile #" << tile->nbrs[ EA ]->id << " at [ " << tile->nbrs[ EA ]->pos[ IX ] << ":" << tile->nbrs[ EA ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ SE ] != nullptr )
		cout << "SE : Tile #" << tile->nbrs[ SE ]->id << " at [ " << tile->nbrs[ SE ]->pos[ IX ] << ":" << tile->nbrs[ SE ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ SO ] != nullptr )
		cout << "SO : Tile #" << tile->nbrs[ SO ]->id << " at [ " << tile->nbrs[ SO ]->pos[ IX ] << ":" << tile->nbrs[ SO ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ SW ] != nullptr )
		cout << "SW : Tile #" << tile->nbrs[ SW ]->id << " at [ " << tile->nbrs[ SW ]->pos[ IX ] << ":" << tile->nbrs[ SW ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ WE ] != nullptr )
		cout << "WE : Tile #" << tile->nbrs[ WE ]->id << " at [ " << tile->nbrs[ WE ]->pos[ IX ] << ":" << tile->nbrs[ WE ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ NW ] != nullptr )
		cout << "NW : Tile #" << tile->nbrs[ NW ]->id << " at [ " << tile->nbrs[ NW ]->pos[ IX ] << ":" << tile->nbrs[ NW ]->pos[ IY ] << " ]" << endl;

	cout << endl;
}

bool areTilesNeighbors( tile_t *tile1, tile_t *tile2 )
{
	if ( tile1->pos[ IX ] == tile2->pos[ IX ] && tile1->pos[ IY ] == tile2->pos[ IY ] )
		return false;
	if ( dif( tile1->pos[ IX ], tile2->pos[ IX ] ) > 1 )
		return false;
	if ( dif( tile1->pos[ IY ], tile2->pos[ IY ] ) > 1 )
		return false;
	return true;
}

void linkTiles( tile_t *tile1, tile_t *tile2 )
{
	if ( !areTilesNeighbors( tile1, tile2 ))
	{
		sstream ss;
		ss << "Tiles [ " << tile1->pos[ IX ] << ":" << tile1->pos[ IY ] << " ] and [ " << tile2->pos[ IX ] << ":" << tile2->pos[ IY ] << " ] are not neighbors";
		//WARN( ss.c_str() , "linkTiles" );
		return;
	}

	if ( tile1->pos[ IX ] > tile2->pos[ IX ])
	{
		if ( tile1->pos[ IY ] > tile2->pos[ IY ])
		{
			tile1->nbrs[ NW ] = tile2;
			tile2->nbrs[ SE ] = tile1;
		}
		else if ( tile1->pos[ IY ] < tile2->pos[ IY ])
		{
			tile1->nbrs[ SW ] = tile2;
			tile2->nbrs[ NE ] = tile1;
		}
		else
		{
			tile1->nbrs[ WE ] = tile2;
			tile2->nbrs[ EA ] = tile1;
		}
	}
	else if ( tile1->pos[ IX ] < tile2->pos[ IX ])
	{
		if ( tile1->pos[ IY ] > tile2->pos[ IY ])
		{
			tile1->nbrs[ NE ] = tile2;
			tile2->nbrs[ SW ] = tile1;
		}
		else if ( tile1->pos[ IY ] < tile2->pos[ IY ])
		{
			tile1->nbrs[ SE ] = tile2;
			tile2->nbrs[ NW ] = tile1;
		}
		else
		{
			tile1->nbrs[ EA ] = tile2;
			tile2->nbrs[ WE ] = tile1;
		}
	}
	else // tile1->pos[ IX ] == tile2->pos[ IX ]
	{
		if ( tile1->pos[ IY ] > tile2->pos[ IY ])
		{
			tile1->nbrs[ NO ] = tile2;
			tile2->nbrs[ SO ] = tile1;
		}
		else if ( tile1->pos[ IY ] < tile2->pos[ IY ])
		{
			tile1->nbrs[ SO ] = tile2;
			tile2->nbrs[ NO ] = tile1;
		}
		else
			WARN( "How did you get here ?!?", "linkTiles" );
	}
}

void linkToNeighbors( tile_t *tile, tile_map_t *map )
{
	uint x = tile->pos[ IX ];
	uint y = tile->pos[ IY ];

	if ( tile->nbrs[ WE ] == nullptr && x > 0 )
		linkTiles( tile, &( *map )[ y + 0 ][ x - 1 ]);

	if ( tile->nbrs[ NW ] == nullptr && x > 0 && y > 0 )
		linkTiles( tile, &( *map )[ y - 1 ][ x - 1 ]);

	if ( tile->nbrs[ NO ] == nullptr && y > 0 )
		linkTiles( tile, &( *map )[ y - 1 ][ x + 0 ]);

	if ( tile->nbrs[ NE ] == nullptr && x < map->size() - 1 && y > 0 )		// NOTE : skip this step in HEX grids (?)
		linkTiles( tile, &( *map )[ y - 1 ][ x + 1 ]);
}

// OBSOLETE
void drawTile( tile_t *tile, uint tileScale, iar2D screenCoords, grid_type_t gridType )
{
	uint tileWidth  = tileScale; // TODO : make this more customizable
	uint tileHeight = tileScale;

	switch ( gridType )
	{
		case GRID_SQR:
			break;
		case GRID_ISO:
			break;
		default:
			ERROR( "Unimplemented grid type", "drawTile" );
			return;
	}


	switch ( tile->type )
	{
		case TILE_EMPTY:
			break;
		case TILE_GRASS:
			DrawRectangle( screenCoords[ IX ], screenCoords[ IY ], tileWidth, tileHeight, GREEN );
			break;
		case TILE_DIRT:
			DrawRectangle( screenCoords[ IX ], screenCoords[ IY ], tileWidth, tileHeight, BROWN );
			break;
		case TILE_SAND:
			DrawRectangle( screenCoords[ IX ], screenCoords[ IY ], tileWidth, tileHeight, YELLOW );
			break;
		case TILE_WATER:
			DrawRectangle( screenCoords[ IX ], screenCoords[ IY ], tileWidth, tileHeight, BLUE );
			break;
		case TILE_ROCK:
			DrawRectangle( screenCoords[ IX ], screenCoords[ IY ], tileWidth, tileHeight, GRAY );
			break;
	}
}
