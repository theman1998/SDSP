#include "SDSPEncoder.h"


SDSPEncoder::SDSPEncoder( const uint8_t * data, uint32_t size ) : messageP{ new uint8_t[size] }, messageSize{ size }
{
	if ( size > 0 )
	{
		std::copy( data, data + size, messageP );
	}
}

SDSPEncoder::SDSPEncoder( const std::string message ) : messageP{ nullptr }, messageSize{ 0 }
{
	if( message.size() != 0 )
	{
		messageP = new char[ message.size() ];
		messageSize = message.size();
		uint8_t * p = ( uint8_t * ) message.c_str();
		std::copy( p, p + messageSize, messageP );
	}
}

SDSPEncoder::~SDSPEncoder()
{
	if( messageP != nullptr )
	{
		delete [] messageP;
	}
}


void SDSPEncoder::insertMessage( std::string message )
{
	if( message.size() == 0 )
	{
		return;
	}
	if( messageP != nullptr )
	{
		delete [] messageP;
	}

	messageP = new char[ message.size() ];
	messageSize = message.size();
	uint8_t * p = ( uint8_t * ) message.c_str();
	std::copy( p, p + messageSize, messageP );
}

void SDSPEncoder::insertMessage( uint8_t * data, uint32_t size )
{
	if( message.size() == 0 )
	{
		return;
	}
	if( messageP != nullptr )
	{
		delete [] messageP;
	}
	messageP = new uint8_t[size];
	std::copy( data, data + size, messageP );
}