/**
 * Copyright (C) 2022-2022 theman1998 bigmaceater589@gmail.com
 * This file belongs to the Simple Drone Serial Protocol
 */

#include "SDSPEncoder.h"

SDSPEncoder::SDSPEncoder() : encodedMessage{ nullptr }, messageSize{0} 
{
}

SDSPEncoder::~SDSPEncoder()
{
	if( encodedMessage != nullptr )
	{
		delete [] encodedMessage;
	}
}

void SDSPEncoder::packer()
{
	messageSize = HEADER_SIZE; // should be comment here

	if ( container.chunkTOLM.isUsed )
	{
		messageSize += container.chunkTOLM.length;
	}
	if ( container.chunkTORM.isUsed )
	{
		messageSize += container.chunkTORM.length;
	}
	if ( container.chunkBOLM.isUsed )
	{
		messageSize += container.chunkBOLM.length;
	}
	if ( container.chunkBORM.isUsed )
	{
		messageSize += container.chunkBORM.length;
	}
	encodedMessage = new uint8_t[messageSize];
	uint32_t byteCounter = packHeader( encodedMessage, messageSize );

	if ( container.chunkTOLM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, container.chunkTOLM );
	}
	if ( container.chunkTORM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, container.chunkTORM );
	}
	if ( container.chunkBOLM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, container.chunkBOLM );
	}
	if ( container.chunkBORM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, container.chunkBORM );
	}
}

uint32_t SDSPEncoder::packHeader( uint8_t * buffer, uint32_t size )
{
	uint32_t byte = 0;
	for( byte; byte < sizeof( SDSP::headerValidation ); byte++ )
	{
		buffer[ byte ] = SDSP::headerValidation[ byte ];
	}
	for ( int i = byte; i < byte + MESSAGE_LENGTH; i++ )
	{
		int ref = i - byte;
		// length is 4 bytes, but our buffer only takes 1 byte
		// this requires us to mask each byte and shift it to the least sigfig
		buffer[i] = ( size & ( 0xFF << (8 * ( MESSAGE_LENGTH - 1 - ref )))) >> ( 8 * ( MESSAGE_LENGTH - 1 - ref ));
		//Serial.print( buffer[i], HEX ); Serial.print(" ");
	}
	//Serial.println( size );
	byte += MESSAGE_LENGTH;
	return byte;
}

uint32_t SDSPEncoder::packMotorChunk( uint8_t * buffer, const SDSP::ChunkMotorControl & chunk )
{
	int byte = 0;
	//length
	for ( byte; byte < CHUNK_SIZE; byte++ )
	{
		// length is 4 bytes, but our buffer only takes 1 byte
		// this requires us to mask each byte and shift it to the least sigfig
		buffer[byte] = ( chunk.length & (0xFF << (8 * ( CHUNK_SIZE - 1 - byte))) ) >> (8 * ( CHUNK_SIZE - 1 - byte));
	}


	for ( int i = 0; i < CHUNK_TYPE_SIZE; i++ )
	{
		buffer[ i + byte ] = chunk.type[ i ];
	}
	byte += CHUNK_TYPE_SIZE;

	buffer[byte++] = ( chunk.speed & 0xFF00 ) >> (8);
	buffer[byte++] = ( chunk.speed & 0xFF );

	return byte;
}


void SDSPEncoder::insertMotorControl( uint16_t speed, SDSP::Types type )
{
	switch( type )
	{
		case SDSP::TOLM:
			container.chunkTOLM.speed = speed;
			container.chunkTOLM.isUsed = true;
			break;
		case SDSP::TORM:
			container.chunkTORM.speed = speed;
			container.chunkTORM.isUsed = true;
			break;
		case SDSP::BOLM:
			container.chunkBOLM.speed = speed;
			container.chunkBOLM.isUsed = true;
			break;
		case SDSP::BORM:
			container.chunkBORM.speed = speed;
			container.chunkBORM.isUsed = true;
			break;
	}
}

uint32_t SDSPEncoder::getPackMessage( uint8_t * out )
{
	uti::copy( encodedMessage, messageSize, out );
	return messageSize;
}

uint32_t SDSPEncoder::getPackSize()
{
	return messageSize;
}