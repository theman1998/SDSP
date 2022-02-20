#ifndef _SDSPENCODER_H_
#define _SDSPENCODER_H_

/**
 * This library is meant to be used with the arduino IDE.
 */
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <String.h>
#include "Utility.h"
#include "SDSP.h"

/**
 * Simple Drone Serial Protocol Encoder will encode and decode messages. 
 */
class SDSPEncoder
{
public:
	SDSPEncoder();
	~SDSPEncoder();

	void initChunks();

	void insertMotorControl( uint16_t speed, SDSP::Types type );

	void packer();

	String getPackMessage();


	uint32_t packHeader( uint8_t * buffer, uint32_t size );
	uint32_t packMotorChunk( uint8_t * buffer, const SDSP::ChunkMotorControl & chunk );


private:
	uint8_t * encodedMessage;
	uint32_t messageSize;

	SDSP::Tangibles container;


};

#endif // _SDSPENCODER_H_
