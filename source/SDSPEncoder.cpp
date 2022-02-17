#include "SDSPEncoder.h"

#define HEADER_SIZE 8

const char headerValidation[] = { (char)0xA5, (char)0x5A, (char)0x69, (char)0x01 };

SDSPEncoder::SDSPEncoder() : encodedMessage{ nullptr }, messageSize{0} 
{}

void SDSPEncoder::initChunks()
{
	ChunkTOLM.type = getTypeString(TOLM);
	ChunkTORM.type = getTypeString(TORM);
	ChunkBOLM.type = getTypeString(BOLM);
	ChunkBORM.type = getTypeString(BORM);
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

	if ( ChunkTOLM.isUsed )
	{
		messageSize += ChunkTOLM.length;
	}
	if ( ChunkTORM.isUsed )
	{
		messageSize += ChunkTORM.length;
	}
	if ( ChunkBOLM.isUsed )
	{
		messageSize += ChunkBOLM.length;
	}
	if ( ChunkBORM.isUsed )
	{
		messageSize += ChunkBORM.length;
	}
	encodedMessage = new uint8_t[messageSize];


	uint32_t byteCounter = HEADER_SIZE; 
	if ( ChunkTOLM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, ChunkTOLM );
	}
	if ( ChunkTORM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, ChunkTORM );
	}
	if ( ChunkBOLM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, ChunkBOLM );
	}
	if ( ChunkBORM.isUsed )
	{
		byteCounter = packMotorChunk( encodedMessage + byteCounter, ChunkBORM );
	}

}

uint32_t SDSPEncoder::packHeader( uint8_t * buffer, uint32_t size )
{
	uint32_t byte = 0;
	for( byte; byte < 4; byte++ )
	{
		buffer[ byte ] = headerValidation[ byte ];
	}
	for ( int i = byte; i < byte + 4; i++ )
	{
		int ref = i - byte;
		// length is 4 bytes, but our buffer only takes 1 byte
		// this requires us to mask each byte and shift it to the least sigfig
		buffer[i] = ( size & (0xFF << (8 * ( 4 - ref))) ) >> (8 * ( 4 - ref));
	}
	byte += 4;


	return byte;
}

uint32_t SDSPEncoder::packMotorChunk( uint8_t * buffer, const SDSPEncoder::ChunkMotorControl & chunk )
{
	int byte = 0;
	//length
	for ( byte; byte < 4; byte++ )
	{
		// length is 4 bytes, but our buffer only takes 1 byte
		// this requires us to mask each byte and shift it to the least sigfig
		buffer[byte] = ( chunk.length & (0xFF << (8 * ( 4 - byte))) ) >> (8 * ( 4 - byte));
	}

	for ( int i = byte; i < byte+4; i++ )
	{
		buffer[ i ] = ( uint8_t ) chunk.type[ i - byte ];
	}
	byte += 4;

	buffer[byte++] = ( chunk.speed & 0xFF00 ) >> (8);
	buffer[byte++] = ( chunk.speed & 0xFF );

	return byte;
}


void SDSPEncoder::insertMotorControl( uint16_t speed, SDSPEncoder::Types type )
{
	switch( type )
	{
		case TOLM:
			ChunkTOLM.speed = speed;
			ChunkTOLM.isUsed = true;
			break;
		case TORM:
			ChunkTORM.speed = speed;
			ChunkTORM.isUsed = true;
			break;
		case BOLM:
			ChunkBOLM.speed = speed;
			ChunkBOLM.isUsed = true;
			break;
		case BORM:
			ChunkBORM.speed = speed;
			ChunkBORM.isUsed = true;
			break;
	}
}

String SDSPEncoder::getTypeString( SDSPEncoder::Types type ) const
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


String SDSPEncoder::getPackMessage()
{
	String res( ( char * ) encodedMessage );	
	return res;
}