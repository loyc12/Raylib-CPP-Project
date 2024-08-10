#include "../inc/deps.hpp"

//void print_debug( const string msg ) { cerr << msg << C_RST << endl; }
void print_msg( const char *type, const char *msg, const char *src_fct, const char *C_COL) { cerr << C_COL << type << ": " << src_fct << "(): " << msg << C_RST << endl; }

void ERROR( const char *msg, const char *src_fct ) { print_msg( "ERROR"  , msg, src_fct, C_RED ); }
void WARN ( const char *msg, const char *src_fct ) { print_msg( "WARNING", msg, src_fct, C_YEL ); }
void INFO ( const char *msg, const char *src_fct ) { print_msg( "INFO"   , msg, src_fct, C_CYN ); }
void DEBUG( const char *msg, const char *src_fct ) { print_msg( "DEBUG"  , msg, src_fct, C_GRN ); }