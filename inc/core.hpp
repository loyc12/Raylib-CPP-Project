#pragma once

#include <raylib.h>

#include "messaging.hpp"
#include "maths.hpp"

/* ==== containers ==== */
#include <array>
#include <vector>

using std::array;
using std::vector;

typedef enum index_e
{
	IX,
	IY,
	IZ,
	IW
}				index_t;

#define iar2D array< int, 2 >
#define iar3D array< int, 3 >
#define iar4D array< int, 4 >

#define uiar2D array< uint, 2 >
#define uiar3D array< uint, 3 >
#define uiar4D array< uint, 4 >





