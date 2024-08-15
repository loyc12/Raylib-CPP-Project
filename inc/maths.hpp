#pragma once

//#include <cmath>

typedef unsigned char byte;

#define iar2D array< int, 2 >
#define iar3D array< int, 3 >
#define iar4D array< int, 4 >

#define uiar2D array< uint, 2 >
#define uiar3D array< uint, 3 >
#define uiar4D array< uint, 4 >

#define TTT template <typename T>

TTT inline T abs( T x )							{ return( x > 0 ? x : -x ); }
TTT inline T sqr( T x )							{ return( x * x ); }
TTT inline T cub( T x )							{ return( x * x * x ); }
TTT inline T sgn( T x )							{ return( x > 0 ? 1 : x < 0 ? -1 : 0 ); }
TTT inline T min( T x, T y )				{ return( x < y ? x : y ); }
TTT inline T max( T x, T y )				{ return( x > y ? x : y ); }
TTT inline T dif( T x, T y )				{ return( x > y ? x - y : y - x ); }
TTT inline T med( T x, T y, T z )		{ return( x < y ? y < z ? y : z : x < z ? x : z ); }
TTT inline T lerp( T a, T b, T t )	{ return( a + t * (b - a) ); }
TTT inline T norm( T x, T a, T b )	{ return( a < b ? (x - a) / (b - a) : (x - b) / (a - b) ); }
TTT inline T clamp( T x, T a, T b )	{ return( a < b ? x < a ? a : x > b ? b : x : x < b ? b : x > a ? a : x ); }

//TTT inline T norm( T x, T min, T max )	{ return ((x - min) / (max - min) ); }
//TTT inline T norm( T x, T a, T b )			{ return ((x - min(a,b)) / (max(a,b) - min(a,b)) ); }

//TTT inline T clamp( T x, T min, T max )	{ return (x < min ? min : x > max ? max : x ); }
//TTT inline T clamp( T x, T a, T b )			{ return (x < min(a,b) ? min(a,b) : x > max(a,b) ? max(a,b) : x ); }
