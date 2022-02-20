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
	bool checkHeader( const uint8_t * data = nullptr );


private:
	uint8_t * messageP;
	uint32_t messageSize;

	SDSP::Tangibles container;

};


#endif // _SDSPDECODER_H_
