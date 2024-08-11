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

/* ==================== Terrain Generation ==================== */


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

/* ==================== Drawing ==================== */

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

/* ==================== Accessors ==================== */

tile_t *Tilemap::getTile( uint x, uint y ) { return &this->map[ y ][ x ]; }
tile_t *Tilemap::setTile( uint x, uint y, tile_type_t _tileType )
{
	this->map[ y ][ x ].type = _tileType;
	return &this->map[ y ][ x ];
}

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

iar2D Tilemap::getOffset() { return this->offset; }
void Tilemap::setOffset( iar2D _offset ) { this->offset = _offset; }
void Tilemap::panMap( iar2D panDir )
{
	this->offset[ IX ] += panDir[ IX ];
	this->offset[ IY ] += panDir[ IY ];
}

void Tilemap::iterOnTiles( void ( *f )( tile_t* ))
{
	for ( uint y = 0; y < this->size; y++ )
	{
		for ( uint x = 0; x < this->size; x++ )
			f( &map[ y ][ x ] );
	}
}

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

uiar2D Tilemap::getTileCoords( uiar2D screenCoords )
{
	uint x = screenCoords[ IX ];
	uint y = screenCoords[ IY ];

	uint tileX = 0;
	uint tileY = 0;

	switch ( this->gridType )
	{
		case GRID_SQR:
			tileX = x / this->tileScale;
			tileY = y / this->tileScale;
			break;
		case GRID_ISO:
		{
			tileX = ( y + x ) / this->tileScale; // TODO : is this broken ???
			tileY = (( 2 * y ) - x ) / this->tileScale;
			break;
		}
		default:
			ERROR( "Unimplemented grid type", "getTileCoords" );
			break;
	}
	return uiar2D{ tileX, tileY };
}

/* ==================== Printing ==================== */

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
