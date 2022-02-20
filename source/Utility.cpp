/**
 * Copyright (C) 2022-2022 theman1998 bigmaceater589@gmail.com
 * This file belongs to the Simple Drone Serial Protocol
 */

#include "Utility.h"

namespace uti
{

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

bool compare( const uint8_t * in, const uint8_t * argument, uint32_t size )
{
	if( size == 0 )
	{
		int breakCounter = 128;
		for ( int i = 0; i < breakCounter; i++ )
		{
			if( argument[size] == 0x00 ) break;
			size++;
		}
	}
	for( int i = 0; i < size; i++ )
	{
		if( in[i] != argument[i] )
		{
			Serial.println( "falseesese ");
			return false; //The 2 arguments are not equal
		}
	}
	return true;
}


}