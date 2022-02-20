/**
 * Copyright (C) 2022-2022 theman1998 bigmaceater589@gmail.com
 * This file belongs to the Simple Drone Serial Protocol
 */

#ifndef _SDSPDECODER_H_
#define _SDSPDECODER_H_

/**
 * This library is meant to be used with the arduino IDE.
 */
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <String.h>
#include "Utility.h"
#include "SDSP.h"

/**
 * Simple Drone Serial Protocol Decoder will decode messages. 
 */
class SDSPDecoder
{

public:
	SDSPDecoder( const uint8_t * data = nullptr, uint32_t size = 0 );
	SDSPDecoder( const String message );
	~SDSPDecoder();

	void insertMessage( String message );
	void insertMessage( uint8_t * data, uint32_t size );

	void parse();
	bool parseHeader( const uint8_t * data = nullptr );
	

private:
	uint8_t * messageP;
	uint32_t messageSize;

	SDSP::Tangibles container;
	
	uint32_t parseChunks( const uint8_t * data );
	uint32_t parseChunkMotor( const uint8_t * data, SDSP::ChunkMotorControl & chunk );

};


#endif // _SDSPDECODER_H_
