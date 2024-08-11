#pragma once

#include <raylib.h>

/* ==== messaging ====*/
#include <string>
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using std::iostream;
using std::istream;
using std::ostream;

using std::fstream;
using std::ifstream;
using std::ofstream;

/* ==== containers ==== */
#include <array>
#include <vector>

using std::array;
using std::vector;

#define arr1 array< int, 1 >
#define arr2 array< int, 2 >
#define arr3 array< int, 3 >

#define IX 0
#define IY 1
#define IZ 2
#define IW 3

/* ==== math ==== */

using std::min;
using std::max;
using std::abs;

/* ==== addons ==== */
#include "colors.hpp"

//void print_debug( const string msg = "..." );
void print_msg( const char *msg, const char *type = "Unspecified", const char *src_fct = "unkown", const char *C_COL = C_DEF );

void ERROR( const char *msg = "Error",   const char *src_fct = "unkown" );
void WARN ( const char *msg = "Warning", const char *src_fct = "unkown" );
void INFO ( const char *msg = "Info",    const char *src_fct = "unkown" );
void DEBUG( const char *msg = "Debug",   const char *src_fct = "unkown" );
