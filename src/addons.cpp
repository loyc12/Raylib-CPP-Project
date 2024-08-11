#include "../inc/core.hpp"

// TODO : add automatic time logging
// TODO : allow outputting to log file instead

void print_msg( const char *type, const char *msg, const char *src_fct, const char *C_COL) { cerr << C_COL << type << ": " << src_fct << "(): " << msg << C_RST << endl; }

void ERROR( const char *msg, const char *src_fct )
{
	if ( LOG_LVL >= ERROR_LVL )
		print_msg( "ERROR", msg, src_fct, C_RED );
}
void WARN ( const char *msg, const char *src_fct )
{
	if ( LOG_LVL >= WARN_LVL )
		print_msg( "WARN ", msg, src_fct, C_YEL );
}
void INFO ( const char *msg, const char *src_fct )
{
	if ( LOG_LVL >= INFO_LVL )
		print_msg( "INFO ", msg, src_fct, C_GRN );
}
void DEBUG( const char *msg, const char *src_fct )
{
	if ( LOG_LVL >= DEBUG_LVL )
		print_msg( "DEBUG", msg, src_fct, C_CYN );
}