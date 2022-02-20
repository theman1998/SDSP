#include "SDSPEncoder.h"

SDSPEncoder::SDSPEncoder() : encodedMessage{ nullptr }, messageSize{0} 
{}

void SDSPEncoder::initChunks()
{
	container.chunkTOLM.type = SDSP::getTypeString(SDSP::TOLM);
	container.chunkTORM.type = SDSP::getTypeString(SDSP::TORM);
	container.chunkBOLM.type = SDSP::getTypeString(SDSP::BOLM);
	container.chunkBORM.type = SDSP::getTypeString(SDSP::BORM);
}

SDSPEncoder::~SDSPEncoder()
{
	if( encodedMessage != nullptr )
	{
    Serial.print("Encoded message contains nullptr; Deleting..");
		delete [] encodedMessage;
	}
}

void SDSPEncoder::packer() //Adjusts packet size in accordance to protocal standards.
{
	messageSize = HEADER_SIZE; //Beginning at the 8th byte; 0 to 7 reserved for header

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
	encodedMessage = new uint8_t [messageSize]; 
  packHeader(encodedMessage,messageSize);
  
  /*Note: At this point, The first 4 Elements are the 
   * validation sequence, the following 4 elements are empty (0), 
   * with the exception the 7th element, it is has a DEC value of 10,
   * a hex value of 16, and a plain print value of 18 :?
  */

	uint32_t byteCounter = HEADER_SIZE; 
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
	for( byte; byte < 4; byte++ )
	{
    //Serial.print(SDSP::headerValidation[byte],HEX);
		buffer[ byte ] = SDSP::headerValidation[ byte ];
	}
	for ( int i = byte; i < byte + 4; i++ )
	{
		int ref = i - byte;
		// length is 4 bytes, but our buffer only takes 1 byte
		// this requires us to mask each byte and shift it to the least sigfig
		buffer[i] = ( size & (0xFF << (8 * ( 3 - ref))) ) >> (8 * ( 3 - ref));
	}
 
	byte += 4;

	return byte;
}

uint32_t SDSPEncoder::packMotorChunk( uint8_t * buffer, const SDSP::ChunkMotorControl & chunk )
{
	int byte = 0;
	//length
	for ( byte; byte < 4; byte++ )
	{
		// length is 4 bytes, but our buffer only takes 1 byte
		// this requires us to mask each byte and shift it to the least sigfig
		buffer[byte] = ( chunk.length & (0xFF << (8 * ( 3 - byte))) ) >> (8 * ( 3 - byte));
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

String SDSPEncoder::getPackMessage()
{
	String res( ( char * ) encodedMessage );	
	return res;
}
