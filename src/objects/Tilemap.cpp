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
			cout << "::";
			break;
		case TILE_ROCK:
			cout << "XX";
			break;
	}
}

void printFullTile( t_tile *tile )
{
	cout << "Tile #" << tile->id << " at [ " << tile->pos[ IX ] << ":" << tile->pos[ IY ] << " ]" << endl;

	if ( tile->no != nullptr )
		cout << "no : Tile #" << tile->no->id << " at [ " << tile->no->pos[ IX ] << ":" << tile->no->pos[ IY ] << " ]" << endl;
	if ( tile->ne != nullptr )
		cout << "ne : Tile #" << tile->ne->id << " at [ " << tile->ne->pos[ IX ] << ":" << tile->ne->pos[ IY ] << " ]" << endl;
	if ( tile->ea != nullptr )
		cout << "ea : Tile #" << tile->ea->id << " at [ " << tile->ea->pos[ IX ] << ":" << tile->ea->pos[ IY ] << " ]" << endl;
	if ( tile->se != nullptr )
		cout << "se : Tile #" << tile->se->id << " at [ " << tile->se->pos[ IX ] << ":" << tile->se->pos[ IY ] << " ]" << endl;
	if ( tile->so != nullptr )
		cout << "so : Tile #" << tile->so->id << " at [ " << tile->so->pos[ IX ] << ":" << tile->so->pos[ IY ] << " ]" << endl;
	if ( tile->sw != nullptr )
		cout << "sw : Tile #" << tile->sw->id << " at [ " << tile->sw->pos[ IX ] << ":" << tile->sw->pos[ IY ] << " ]" << endl;
	if ( tile->we != nullptr )
		cout << "we : Tile #" << tile->we->id << " at [ " << tile->we->pos[ IX ] << ":" << tile->we->pos[ IY ] << " ]" << endl;
	if ( tile->nw != nullptr )
		cout << "nw : Tile #" << tile->nw->id << " at [ " << tile->nw->pos[ IX ] << ":" << tile->nw->pos[ IY ] << " ]" << endl;

	cout << endl;
}

bool areTilesNeighbors( t_tile *tile1, t_tile *tile2 )
{
	if ( tile1->pos[ IX ] == tile2->pos[ IX ] && tile1->pos[ IY ] == tile2->pos[ IY ] )
		return false;
	if ( abs( tile1->pos[ IX ] - tile2->pos[ IX ] ) > 1 )
		return false;
	if ( abs( tile1->pos[ IY ] - tile2->pos[ IY ] ) > 1 )
		return false;
	return true;
}

void linkTiles( t_tile *tile1, t_tile *tile2 )
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
			tile1->nw = tile2;
			tile2->se = tile1;
		}
		else if ( tile1->pos[ IY ] < tile2->pos[ IY ])
		{
			tile1->sw = tile2;
			tile2->ne = tile1;
		}
		else
		{
			tile1->we = tile2;
			tile2->ea = tile1;
		}
	}
	else if ( tile1->pos[ IX ] < tile2->pos[ IX ])
	{
		if ( tile1->pos[ IY ] > tile2->pos[ IY ])
		{
			tile1->ne = tile2;
			tile2->sw = tile1;
		}
		else if ( tile1->pos[ IY ] < tile2->pos[ IY ])
		{
			tile1->se = tile2;
			tile2->nw = tile1;
		}
		else
		{
			tile1->ea = tile2;
			tile2->we = tile1;
		}
	}
	else // tile1->pos[ IX ] == tile2->pos[ IX ]
	{
		if ( tile1->pos[ IY ] > tile2->pos[ IY ])
		{
			tile1->no = tile2;
			tile2->so = tile1;
		}
		else if ( tile1->pos[ IY ] < tile2->pos[ IY ])
		{
			tile1->so = tile2;
			tile2->no = tile1;
		}
		else
			WARN( "How did you get here ?!?", "linkTiles" );
	}
}

t_tile_type randomTileType()
{
	t_tile_type tileType = TILE_EMPTY;

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


Tilemap::Tilemap( uint _size, t_grid_type _gridType )
{
	this->size = _size;
	this->maxTileID = 0;
	this->offset = arr2{ 0, 0 }; // TODO : center it ( via map dimensions )
	this->gridType = _gridType;
	this->map = t_tile_map( this->size, t_tile_row( this->size ));

	this->initMap();
}

void Tilemap::initMap()
{
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
		{
			t_tile *newTile = &( this->map[ y ][ x ]);

			newTile->id = this->maxTileID++;
			newTile->pos = arr2{ (int)x, (int)y };

			newTile->isPopulated = false;
			newTile->type = TILE_EMPTY;

			// Linking bidirectionally with neighbors
			if ( x > 0 )
				linkTiles( newTile, (t_tile *)&( this->map[ y + 0 ][ x - 1 ]));
			if ( x > 0 && y > 0 )
				linkTiles( newTile, (t_tile *)&( this->map[ y - 1 ][ x - 1 ]));
			if ( y > 0 )
				linkTiles( newTile, (t_tile *)&( this->map[ y - 1 ][ x + 0 ]));
			if ( x < this->size - 1 && y > 0 ) //																						NOTE : skip this step in HEX grids (?)
				linkTiles( newTile, (t_tile *)&( this->map[ y - 1 ][ x + 1 ]));
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

t_tile *Tilemap::getTile( uint x, uint y ) { return &this->map[ y ][ x ]; }
t_tile *Tilemap::setTile( uint x, uint y, t_tile_type _tileType )
{
	this->map[ y ][ x ].type = _tileType;
	return &this->map[ y ][ x ];
}

void Tilemap::setOffset( uint x, uint y ) { this->offset = arr2{ (int)x, (int)y }; }
void Tilemap::setOffset( arr2 _offset ) { this->offset = _offset; }
arr2 Tilemap::getOffset() { return this->offset; }

void Tilemap::iterOnTiles( void ( *f )( t_tile* ))
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
