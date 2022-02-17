#include "SDSPDecoder.h"


SDSPDecoder::SDSPDecoder( const uint8_t * data, uint32_t size ) : messageP{ new uint8_t[size] }, messageSize{ size }
{
	if ( size > 0 )
	{
		copy( data, size, messageP );
	}
}

SDSPDecoder::SDSPDecoder( const String message ) : messageP{ nullptr }, messageSize{ 0 }
{
	if( message.length() != 0 )
	{
		messageP = new uint8_t[ message.length() ];
		messageSize = message.length();
		uint8_t * p = ( uint8_t * ) message.c_str();
		copy( p, messageSize, messageP );
	}
}

SDSPDecoder::~SDSPDecoder()
{
	if( messageP != nullptr )
	{
		delete [] messageP;
	}
}


void SDSPDecoder::insertMessage( String message )
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

void SDSPDecoder::insertMessage( uint8_t * data, uint32_t size )
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

String SDSPDecoder::getTypeString( SDSPDecoder::Types type ) const
{
	switch( type )
	{
		case TOLM: return "TOLM";
		case TORM: return "TORM";
		case BOLM: return "BOLM";
		case BORM: return "BORM";
	}
	return "";
}
