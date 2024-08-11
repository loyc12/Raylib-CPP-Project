#include "../../inc/Tilemap.hpp"

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

	if ( tile->nbrs[ NO ] != nullptr )
		cout << "no : Tile #" << tile->nbrs[ NO ]->id << " at [ " << tile->nbrs[ NO ]->pos[ IX ] << ":" << tile->nbrs[ NO ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ NE ] != nullptr )
		cout << "ne : Tile #" << tile->nbrs[ NE ]->id << " at [ " << tile->nbrs[ NE ]->pos[ IX ] << ":" << tile->nbrs[ NE ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ EA ] != nullptr )
		cout << "ea : Tile #" << tile->nbrs[ EA ]->id << " at [ " << tile->nbrs[ EA ]->pos[ IX ] << ":" << tile->nbrs[ EA ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ SE ] != nullptr )
		cout << "se : Tile #" << tile->nbrs[ SE ]->id << " at [ " << tile->nbrs[ SE ]->pos[ IX ] << ":" << tile->nbrs[ SE ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ SO ] != nullptr )
		cout << "so : Tile #" << tile->nbrs[ SO ]->id << " at [ " << tile->nbrs[ SO ]->pos[ IX ] << ":" << tile->nbrs[ SO ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ SW ] != nullptr )
		cout << "sw : Tile #" << tile->nbrs[ SW ]->id << " at [ " << tile->nbrs[ SW ]->pos[ IX ] << ":" << tile->nbrs[ SW ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ WE ] != nullptr )
		cout << "we : Tile #" << tile->nbrs[ WE ]->id << " at [ " << tile->nbrs[ WE ]->pos[ IX ] << ":" << tile->nbrs[ WE ]->pos[ IY ] << " ]" << endl;
	if ( tile->nbrs[ NW ] != nullptr )
		cout << "nw : Tile #" << tile->nbrs[ NW ]->id << " at [ " << tile->nbrs[ NW ]->pos[ IX ] << ":" << tile->nbrs[ NW ]->pos[ IY ] << " ]" << endl;

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
		//WARN( ss.str().c_str() , "linkTiles" );
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

tile_type_t randomTileType()
{
	tile_type_t tileType = TILE_EMPTY;

	byte r = rand() % 4;
	switch ( r )
	{
		case 0:
			tileType = TILE_GRASS;
			break;
		case 1:
			tileType = TILE_SAND;
			break;
		case 2:
			tileType = TILE_WATER;
			break;
		case 3:
			tileType = TILE_ROCK;
			break;
	}
	// TODO : change tileType based on neighbours here

	return tileType;
}


/* ================ Tilemap Class ================ */


Tilemap::Tilemap( uint _size, grid_type_t _gridType )
{
	this->size = _size;
	this->maxTileID = 0;
	this->offset = uiar2D{ 0, 0 }; // TODO : center it ( via map dimensions )
	this->gridType = _gridType;
	this->map = tile_map_t( this->size, tile_row_t( this->size ));

	this->initMap();
}

void Tilemap::initMap()
{
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
		{
			tile_t *newTile = &( this->map[ y ][ x ]);

			newTile->id = this->maxTileID++;
			newTile->pos = uiar2D{ x, y };

			newTile->isPopulated = false;
			newTile->type = TILE_EMPTY;

			linkToNeighbors( newTile, &( this->map ));
		}
	}
}


Tilemap::~Tilemap() { this->clearMap(); }

void Tilemap::clearMap()
{
	for ( uint y = 0; y < this->size; y++ )
		this->map[y].clear();
	this->map.clear();
}

void Tilemap::populateMap()
{
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
		{
			if ( this->map[ y ][ x ].isPopulated )
				continue;

			this->map[ y ][ x ].type = randomTileType();
			this->map[ y ][ x ].isPopulated = true;
		}
	}
}

tile_t *Tilemap::getTile( uint x, uint y ) { return &this->map[ y ][ x ]; }
tile_t *Tilemap::setTile( uint x, uint y, tile_type_t _tileType )
{
	this->map[ y ][ x ].type = _tileType;
	return &this->map[ y ][ x ];
}

void Tilemap::setOffset( uint x, uint y ) { this->offset = uiar2D{ x, y }; }
void Tilemap::setOffset( uiar2D _offset ) { this->offset = _offset; }
uiar2D Tilemap::getOffset() { return this->offset; }

void Tilemap::iterOnTiles( void ( *f )( tile_t* ))
{
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
			f( &map[ y ][ x ] );
	}
}

void Tilemap::printTileAt( uint x, uint y ) { printTile( &this->map[ y ][ x ] ); }
void Tilemap::printMap()
{
	cout << "Tilemap : " << this->size << "x" << this->size << endl << endl;
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
			printTile( &this->map[ y ][ x ] );
		cout << endl;
	}
	cout << endl;
}
