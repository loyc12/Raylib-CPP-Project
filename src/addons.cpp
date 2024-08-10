#include "../inc/deps.hpp"

void print_debug( const string msg ) { cerr << msg << C_RST << endl; }
void print_error( const char *msg, const char *type, const char *src, const char *C_COL)
{
	print_debug( string( C_COL ) + type + " : " + src + "() : " + msg );
}

void ERROR( const char *msg, const char *src ) { print_error( msg, "ERROR"  , src, C_RED ); }
void WARN ( const char *msg, const char *src ) { print_error( msg, "WARNING", src, C_YEL ); }
void INFO ( const char *msg, const char *src ) { print_error( msg, "INFO"   , src, C_CYN ); }
void DEBUG( const char *msg, const char *src ) { print_error( msg, "DEBUG"  , src, C_GRN ); }