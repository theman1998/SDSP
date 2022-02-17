#ifndef _SDSPENCODER_H_
#define _SDSPENCODER_H_

/**
 * This library is meant to be used with the arduino IDE.
 */
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <String.h>

/**
 * Simple Drone Serial Protocol Encoder will encode and decode messages. 
 */
class SDSPEncoder
{

public:
	SDSPEncoder( const uint8_t * data = nullptr, uint32_t size = 0, bool encodedMessage );
	SDSPEncoder( const String message );
	~SDSPEncoder();

	void insertMessage( String message );
	void insertMessage( uint8_t * data, uint32_t size );



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

void copy( const char * in, uint32_t size, char * out);
void copy( const uint8_t * in, uint32_t size, uint8_t * out);


#endif // _SDSPENCODER_H_
