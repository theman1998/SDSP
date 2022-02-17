#include "SDSPEncoder.h"


SDSPEncoder::SDSPEncoder( const uint8_t * data, uint32_t size ) : messageP{ new uint8_t[size] }, messageSize{ size }
{
	if ( size > 0 )
	{
		copy( data, size, messageP );
	}
}

SDSPEncoder::SDSPEncoder( const String message ) : messageP{ nullptr }, messageSize{ 0 }
{
	if( message.length() != 0 )
	{
		messageP = new uint8_t[ message.length() ];
		messageSize = message.length();
		uint8_t * p = ( uint8_t * ) message.c_str();
		copy( p, messageSize, messageP );
	}
}

SDSPEncoder::~SDSPEncoder()
{
	if( messageP != nullptr )
	{
		delete [] messageP;
	}
}


void SDSPEncoder::insertMessage( String message )
{
	if( message.length() == 0 )
	{
		return;
	}
	if( messageP != nullptr )
	{
		delete [] messageP;
	}

	messageP = new uint8_t[ message.length() ];
	messageSize = message.length();
	uint8_t * p = ( uint8_t * ) message.c_str();
	copy( p, messageSize, messageP );
}

void SDSPEncoder::insertMessage( uint8_t * data, uint32_t size )
{
	if( size == 0 )
	{
		return;
	}
	if( messageP != nullptr )
	{
		delete [] messageP;
	}
	messageP = new uint8_t[size];
	copy( data, size, messageP );
}








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