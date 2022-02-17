#ifndef _SDSPDECODER_H_
#define _SDSPDECODER_H_

/**
 * This library is meant to be used with the arduino IDE.
 */
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <String.h>
#include "Utility.h"

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

	void packer();

	enum Types
	{
		TOLM,
		TORM,
		BOLM,
		BORM
	};
	String getTypeString( SDSPDecoder::Types type ) const;

	struct Header
	{
		bool valid			{false};
		uint32_t length		{0};
	};
	struct Chunk
	{
		uint32_t length		{0};
		String type			{""};
		uint8_t * data 		{nullptr};
	};



private:
	uint8_t * messageP;
	uint32_t messageSize;

};


#endif // _SDSPDECODER_H_
