/**
 * Copyright (C) 2022-2022 theman1998 bigmaceater589@gmail.com
 * This file belongs to the Simple Drone Serial Protocol
 */

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

	void insertMotorControl( uint16_t speed, SDSP::Types type );

	void packer();

	// does not work, as the string will cut out once it hits a eliminator(aka 0x00). no way to tell this String library the size of the array
	//String getPackMessage();
	uint32_t getPackMessage( uint8_t * out );
	uint32_t getPackSize();


	uint32_t packHeader( uint8_t * buffer, uint32_t size );
	uint32_t packMotorChunk( uint8_t * buffer, const SDSP::ChunkMotorControl & chunk );


private:
	uint8_t * encodedMessage;
	uint32_t messageSize;

	SDSP::Tangibles container;


};

#endif // _SDSPENCODER_H_
