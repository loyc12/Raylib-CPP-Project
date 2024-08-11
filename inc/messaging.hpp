#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "colors.hpp"

typedef enum log_lvl_e { ERROR_LVL, WARN_LVL, INFO_LVL, DEBUG_LVL } log_lvl_t;

#define LOG_LVL INFO_LVL

using std::cin;
using std::cout;
using std::cerr;

using std::endl;
typedef std::string str;

using std::iostream;
using std::istream;
using std::ostream;

using std::fstream;
using std::ifstream;
using std::ofstream;

// custom stringstream class that allows for c_str() method
class ExtendedStringStream : public std::stringstream
{
	private: std::string 	cached_str;
	public:  const char*	c_str()  { cached_str = this->str();  return ( cached_str.c_str() ); }
};
typedef ExtendedStringStream sstream;

/* ================ from Addons.cpp ================ */

void print_msg( const char *msg, const char *type = "Unspecified", const char *src_fct = "unkown", const char *C_COL = C_DEF );

void ERROR( const char *msg = "Error",   const char *src_fct = "unkown" );
void WARN ( const char *msg = "Warning", const char *src_fct = "unkown" );
void INFO ( const char *msg = "Info",    const char *src_fct = "unkown" );
void DEBUG( const char *msg = "Debug",   const char *src_fct = "unkown" );