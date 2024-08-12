#include "../../inc/Tilemap.hpp"


Tilemap::Tilemap( uint _size, grid_type_t _gridType ): size( _size ), tileScale( NEW_TILE_SCALE ), maxTileID( 0 ), gridType( _gridType )
{
	this->offset = iar2D{ 0, 0 }; // TODO : center it ( via map dimensions )

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

/* ================ Terrain Generation ================ */


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

/* ====================== Drawing ===================== */

// OBSOLETE
void Tilemap::drawMap()
{
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
		{
			tile_t *tile = &this->map[ y ][ x ];

			iar2D screenCoords = this->getScreenCoords( tile->pos );

			// skip drawing if tile is offscreen
			if ( screenCoords[ IX ] <= -(int)this->tileScale || screenCoords[ IX ] > GetScreenWidth() ||
					 screenCoords[ IY ] <= -(int)this->tileScale || screenCoords[ IY ] > GetScreenHeight())
				continue;

			drawTile( tile, this->tileScale, this->getScreenCoords( tile->pos ), this->gridType );
		}
	}
}

/* ===================== Accessors ==================== */

iar2D Tilemap::getScreenCoords( uiar2D tileCoords )
{
	uint x = tileCoords[ IX ];
	uint y = tileCoords[ IY ];

	int screenX = 0;
	int screenY = 0;

	switch ( this->gridType )
	{
		case GRID_SQR:
			screenX = x * this->tileScale;
			screenY = y * this->tileScale;
			break;

		case GRID_ISO:
			screenX = ( x - y ) * this->tileScale;
			screenY = ( x + y ) * this->tileScale / 2;
			break;

		default:
			ERROR( "Unimplemented grid type", "getScreenCoords" );
			break;
	}
	return iar2D{ screenX + this->offset[ IX ], screenY + this->offset[ IY ] };
}

tile_t *Tilemap::getTileAt( uiar2D screenCoords )
{
	uint screenX = screenCoords[ IX ] - this->offset[ IX ];
	uint screenY = screenCoords[ IY ] - this->offset[ IY ];

	uint halfTile = this->tileScale / 2;
	uint tileX = 0;
	uint tileY = 0;

	switch ( this->gridType )
	{
		case GRID_SQR:
			tileX = screenX / this->tileScale;
			tileY = screenY / this->tileScale;
			break;

		case GRID_ISO:
			tileX = (( 2 * screenY ) + ( screenX - halfTile )) / ( 2 * this->tileScale ); // NOTE : DON'T CHANGE THIS
			tileY = (( 2 * screenY ) - ( screenX - halfTile )) / ( 2 * this->tileScale ); // I HAD TO MATH IT OUT !!!
			break;

		default:
			ERROR( "Unimplemented grid type", "getTileAt" );
			return nullptr;
	}
	return this->getTile( tileX, tileY );
}

tile_t *Tilemap::getTile( uint x, uint y )
{
	if ( !this->isTileValid( x, y ))
		return nullptr;
	return &this->map[ y ][ x ];
}
tile_t *Tilemap::setTile( uint x, uint y, tile_type_t _tileType )
{
	if ( !this->isTileValid( x, y ))
		return nullptr;
	this->map[ y ][ x ].type = _tileType;
	return &this->map[ y ][ x ];
}

uint Tilemap::getSize() { return this->size; }
uint Tilemap::getZoom() { return this->tileScale; }
void Tilemap::setZoom( uint _tileScale )
{
	if ( _tileScale < MIN_TILE_SCALE )
		this->tileScale = MIN_TILE_SCALE;
	else if ( _tileScale > MAX_TILE_SCALE )
		this->tileScale = MAX_TILE_SCALE;
	else
		this->tileScale = _tileScale;
}
void Tilemap::zoomMap( int delta ) { this->setZoom( this->tileScale + delta ); }

iar2D Tilemap::getOffset() { return this->offset; }
void Tilemap::setOffset( iar2D _offset ) { this->offset = _offset; }
void Tilemap::modOffset( iar2D delta )
{
	this->offset[ IX ] += delta[ IX ];
	this->offset[ IY ] += delta[ IY ];
}

void Tilemap::iterOnTiles( void ( *f )( tile_t* ))
{
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
			f( &map[ y ][ x ] );
	}
}

bool Tilemap::isTileValid( uint x, uint y )
{
	if ( x >= this->size || y >= this->size )
	{
		INFO( "Tile is out of bounds", "isTileValid" );
		return false;
	}
	return true;
}

/* ================== Debug Printing ================== */

void Tilemap::printTileAt( uint x, uint y )
{
	if ( this->isTileValid( x, y ))
	printTile( &this->map[ y ][ x ] );
}
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
