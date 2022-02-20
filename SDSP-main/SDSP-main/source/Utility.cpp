#include "Utility.h"

// ------------------- can't use the standard library functions -----------------------------
void copy( const char * in, uint32_t size, char * out)
{
	for ( uint32_t i = 0; i < size; i++ )
	{
		out[i] = in[i];
	}
}
void copy( const uint8_t * in, uint32_t size, uint8_t * out)
{
	for ( uint32_t i = 0; i < size; i++ )
	{
		out[i] = in[i];
	}
}