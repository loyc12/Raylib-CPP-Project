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

using std::iostream;
using std::istream;
using std::ostream;

using std::fstream;
using std::ifstream;
using std::ofstream;

/* ==== containers ==== */
#include <vector>

using std::string;
using std::vector;

/* ==== math ==== */

using std::min;
using std::max;
using std::abs;

/* ==== addons ==== */
#include "colors.hpp"

void print_debug( const string msg = "Debug" );
void print_error( const char *msg, const char *type = "Error", const char *src = "unkown", const char *C_COL = C_DEF );

void ERROR( const char *msg = "Error", const char *src = "unkown" );
void WARN ( const char *msg = "Warning", const char *src = "unkown" );
void INFO ( const char *msg = "Info", const char *src = "unkown" );
void DEBUG( const char *msg = "Debug", const char *src = "unkown" );
