#ifndef _SDSPENCODER_H_
#define _SDSPENCODER_H_

/**
 * This library is meant to be used with the arduino IDE.
 */
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <String.h>
#include "Utility.h"

/**
 * Simple Drone Serial Protocol Encoder will encode and decode messages. 
 */
class SDSPEncoder
{
public:
	struct Chunk
	{
		uint32_t length		{0};
		String type			{""};
		uint8_t * data 		{nullptr};
	};	
	enum Types
	{
		TOLM,
		TORM,
		BOLM,
		BORM
	};
	struct ChunkMotorControl
	{
		const uint32_t length	{10}; // This will always be 10 with current structure. 4 + 4 + 2
		String type				{""};
		uint16_t speed			{0}; // speed that the ESC will operate at. Motor will start at speed 1150, and can go above 2k
		bool isUsed				{false};
	};

	struct Header
	{
		bool valid			{false};
		uint32_t length		{0};
	};


	SDSPEncoder();
	~SDSPEncoder();

	void initChunks();

	void insertMotorControl( uint16_t speed, SDSPEncoder::Types type );

	void packer();

	String getPackMessage();


	uint32_t packHeader( uint8_t * buffer, uint32_t size );
	uint32_t packMotorChunk( uint8_t * buffer, const SDSPEncoder::ChunkMotorControl & chunk );


	String getTypeString( SDSPEncoder::Types type ) const;






private:
	uint8_t * encodedMessage;
	uint32_t messageSize;

	ChunkMotorControl ChunkTOLM;
	ChunkMotorControl ChunkTORM;
	ChunkMotorControl ChunkBOLM;
	ChunkMotorControl ChunkBORM;

};

#endif // _SDSPENCODER_H_
