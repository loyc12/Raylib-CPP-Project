#include "../../inc/Engine.hpp"
#include "../../inc/graphics.hpp"

void Engine::graphicsStep()
{
	DEBUG( "Here", "graphicsStep" );

}

void Engine::drawingStep()
{
	DEBUG( "Here", "drawingStep" );
	BeginDrawing();

	ClearBackground( BKGRND_COLOR );

	if ( NO_MAP_TEXTURE )
		this->tilemap->drawMapDebug();
	else
	{
		for ( uint i = 0; i < this->tilemap->getSize(); i++ )
		{
			for ( uint j = 0; j < this->tilemap->getSize(); j++ )
			{
				tile_t *tile = this->tilemap->getTile( i, j );
				if ( tile )
				{
					iar2D screenPos = this->tilemap->getScreenCoords( tile->pos );
					if ( this->isOnScreen( screenPos ))
						this->drawTile( tile->type, screenPos );
				}
			}
		}
	}

	EndDrawing();
}

bool Engine::isOnScreen( iar2D screenPos )
{
	DEBUG( "Here", "isOnScreen" );

	int tileSize = 2 * int( this->tilemap->getTileScale() );

	if ( screenPos[ IX ] <= -tileSize || screenPos[ IX ] > GetScreenWidth() ||
			 screenPos[ IY ] <= -tileSize || screenPos[ IY ] > GetScreenHeight())
		return false;
	return true;
}

void DrawTileFromTextureID( tile_texture_id_t ID, float screenX, float screenY, float scale, Texture2D tileAtlas )
{
	uint atlasW = tileAtlas.width / SPRITE_RES;
	uint atlasH = tileAtlas.height / SPRITE_RES;

	float atlasX = uint(( ID % atlasW ) * SPRITE_RES );
	float atlasY = uint(( ID / atlasH ) * SPRITE_RES );

	Rectangle sourceRec = { atlasX, atlasY, SPRITE_RES, SPRITE_RES };
	Rectangle destRec =   { screenX, screenY, scale, scale };

	// use Raylib to draw the correct portion of the texture atlas onto the screen
	DrawTexturePro( tileAtlas, sourceRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE );
}

void Engine::drawTile( tile_type_t tileType, iar2D screenPos )
{
	DEBUG( "Here", "DrawTile" );

	// only made for isometric grids

	float screenX = float( screenPos[ IX ]);
	float screenY = float( screenPos[ IY ]);
	float scale =   float( this->tilemap->getTileScale() );

	switch ( this->tilemap->getGridType() )
	{
		case GRID_ISO:
			scale *= 2;
			break;
		default: // implement the rest
			break;
	}

	switch ( tileType )
	{
		case TILE_EMPTY:
			DrawTileFromTextureID( TID_TILE_EMPTY, screenX, screenY, scale, this->tileAtlas );
			break;
		case TILE_GRASS:
			DrawTileFromTextureID( TID_TILE_GRASS, screenX, screenY, scale, this->tileAtlas );
			break;
		case TILE_DIRT:
			DrawTileFromTextureID( TID_TILE_DIRT,  screenX, screenY, scale, this->tileAtlas );
			break;
		case TILE_SAND:
			DrawTileFromTextureID( TID_TILE_SAND,  screenX, screenY, scale, this->tileAtlas );
			break;
		case TILE_WATER:
			DrawTileFromTextureID( TID_TILE_WATER, screenX, screenY, scale, this->tileAtlas );
			break;
		case TILE_ROCK:
			DrawTileFromTextureID( TID_TILE_ROCK,  screenX, screenY, scale, this->tileAtlas );
			break;
		default:
			WARN( "Unknown tile type", "drawTile" );
			break;
	}
}
