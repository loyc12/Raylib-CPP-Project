#pragma once

#include <raylib.h>

#define SPRITE_RES 64

typedef enum tile_texture_id_e
{
	TID_TILE_EMPTY,
	TID_TILE_GRASS,
	TID_TILE_DIRT,
	TID_TILE_WATER,
	TID_TILE_SAND,
	TID_TILE_ROCK
}				tile_texture_id_t;