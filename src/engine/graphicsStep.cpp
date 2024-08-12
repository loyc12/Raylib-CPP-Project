#include "../../inc/Engine.hpp"
#include <raylib.h>


void Engine::graphicsStep()
{
	DEBUG( "Here", "graphicsStep" );

}

void Engine::drawingStep()
{
	DEBUG( "Here", "drawingStep" );
	BeginDrawing();
	ClearBackground( BKGRND_COLOR );

	// OBSOLETE
	//this->tilemap->drawMap();

	for ( uint i = 0; i < this->tilemap->getSize(); i++ )
	{
		for ( uint j = 0; j < this->tilemap->getSize(); j++ )
		{;
			tile_t *tile = this->tilemap->getTile( i, j );
			iar2D screenPos = this->tilemap->getScreenCoords( tile->pos );
			this->drawTile( tile->type, screenPos );
		}
	}

	EndDrawing();
}


void DrawTileFromTextureID( tile_texture_id_t ID, float screenX, float screenY, Texture2D tileAtlas )
{
	uint atlasW = tileAtlas.width / SPRITE_RES;
	uint atlasH = tileAtlas.height / SPRITE_RES;

	uint atlasX = ( ID % atlasW ) * SPRITE_RES;
	uint atlasY = ( ID / atlasH ) * SPRITE_RES;

	Rectangle sourceRec = { (float)atlasX, (float)atlasY, SPRITE_RES, SPRITE_RES };

	// use openGL to draw the correct portion of the texture atlas onto the screen
	DrawTextureRec( tileAtlas, sourceRec, (Vector2){ screenX, screenY }, WHITE );
}

void Engine::drawTile( tile_type_t tileType, iar2D screenPos )
{
	DEBUG( "Here", "DrawTile" );

	float screenX = ( float )screenPos[ IX ];
	float screenY = ( float )screenPos[ IY ];

	switch ( tileType )
	{
		case TILE_EMPTY:
			DrawTileFromTextureID( TID_TILE_EMPTY, screenX, screenY, this->tileAtlas );
			break;
		case TILE_GRASS:
			DrawTileFromTextureID( TID_TILE_GRASS, screenX, screenY, this->tileAtlas );
			break;
		case TILE_DIRT:
			DrawTileFromTextureID( TID_TILE_DIRT, screenX, screenY, this->tileAtlas );
			break;
		case TILE_WATER:
			DrawTileFromTextureID( TID_TILE_WATER, screenX, screenY, this->tileAtlas );
			break;
		case TILE_SAND:
			DrawTileFromTextureID( TID_TILE_SAND, screenX, screenY, this->tileAtlas );
			break;
		case TILE_ROCK:
			DrawTileFromTextureID( TID_TILE_ROCK, screenX, screenY, this->tileAtlas );
			break;
		default:
			WARN( "Unknown tile type", "drawTile" );
			break;
	}
}
