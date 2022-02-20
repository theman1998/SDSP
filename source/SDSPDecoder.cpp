/**
 * Copyright (C) 2022-2022 theman1998 bigmaceater589@gmail.com
 * This file belongs to the Simple Drone Serial Protocol
 */

#include "SDSPDecoder.h"


SDSPDecoder::SDSPDecoder( const uint8_t * data, uint32_t size ) : messageP{ new uint8_t[size] }, messageSize{ size }
{
	if ( size > 0 )
	{
		uti::copy( data, size, messageP );
	}
}

SDSPDecoder::SDSPDecoder( const String message ) : messageP{ nullptr }, messageSize{ 0 }
{
	if( message.length() != 0 )
	{
		messageP = new uint8_t[ message.length() ];
		messageSize = message.length();
		uint8_t * p = ( uint8_t * ) message.c_str();
		uti::copy( p, messageSize, messageP );
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
	uti::copy( p, messageSize, messageP );
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
	uti::copy( data, size, messageP );
}

void SDSPDecoder::parse()
{
	bool thisProtocol = parseHeader();
	if ( ! thisProtocol )
	{
		Serial.println( "This is not a SDSP Protocol" );
		return;
	}

	const uint32_t payloadLength = container.header.length - HEADER_SIZE;
	uint32_t position = HEADER_SIZE;

	// will through each chunk, tell we hit the end of the payload
	while( position < payloadLength )
	{
		position += parseChunks( messageP + position );
	}


}


bool SDSPDecoder::parseHeader( const uint8_t * data )
{
	uint8_t * headerP  = ( uint8_t * ) data;
	if( data == nullptr )
	{
		headerP = messageP;
	}

	uint32_t byte = 0;

	for( byte; byte < sizeof( SDSP::headerValidation ); byte++ )
	{
		if( headerP[ byte ] != SDSP::headerValidation[ byte ] )
		{
			container.header.valid = false;
			return false;
		}
	}

	union SDSP::ByteUnion bUnion;
	bUnion.b8 = 0; // clears the entire mem space
	uint32_t sizeOfThisMessage = 0;
	for ( int i = 0; i < MESSAGE_LENGTH; i++ )
	{
		uint8_t & v = headerP[ byte++ ];
		sizeOfThisMessage +=  v  << (8 * ( MESSAGE_LENGTH - 1 - i ));

	}

	container.header.length = sizeOfThisMessage;
	//Serial.print( "Decoder size: ");Serial.println( container.header.length, DEC );
	return true;
}

uint32_t SDSPDecoder::parseChunks( const uint8_t * data )
{
	uint32_t res = 0;
	char typeA[4];

	uint16_t byte = 0;

	// gets the size of this chunk
	for ( byte = 0; byte < CHUNK_SIZE; byte++ )
	{
		res +=  data[byte]  << (8 * ( CHUNK_SIZE - 1 - byte ));
	}

	// get the type for this chunk
	for ( int b = 0; b < CHUNK_TYPE_SIZE; b++ )
	{
		typeA[b] = (char)*( data + b + byte );
	}
	byte += CHUNK_TYPE_SIZE;

	SDSP::Types type = SDSP::getTypeFromString( typeA );
	
	switch ( type )
	{
		case SDSP::TOLM:
			parseChunkMotor( data, container.chunkTOLM);
			break;
		case SDSP::TORM:
			parseChunkMotor( data, container.chunkTORM);
			break;
		case SDSP::BOLM:
			parseChunkMotor( data, container.chunkBOLM);
			break;
		case SDSP::BORM:
			parseChunkMotor( data, container.chunkBORM);
			break;		
	}


	Serial.print( " parseChunks result is: ");Serial.println( res );
	return res;
}

// assumption, the only relevent data is bit 8 & 9, defined by the protocol
uint32_t SDSPDecoder::parseChunkMotor( const uint8_t * data, SDSP::ChunkMotorControl & chunk)
{
	chunk.isUsed = true;
	chunk.speed = ( data[ CHUNK_KNOWN_SIZE ] << 8 )  + data[ CHUNK_KNOWN_SIZE + 1 ];

	//Serial.print( "motor speed is " ); Serial.println( chunk.speed );
	return CHUNK_MOTOR_DATA_SIZE + CHUNK_KNOWN_SIZE;
}