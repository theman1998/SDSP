/**
 * Copyright (C) 2022-2022 theman1998 bigmaceater589@gmail.com
 * This file belongs to the Simple Drone Serial Protocol
 */

#ifndef _SDSP_H_
#define _SDSP_H_

#define MESSAGE_LENGTH 4
#define VALIDATION_LENGTH 4
#define HEADER_SIZE VALIDATION_LENGTH + MESSAGE_LENGTH

#define CHUNK_SIZE 4
#define CHUNK_TYPE_SIZE 4
#define CHUNK_KNOWN_SIZE CHUNK_SIZE + CHUNK_TYPE_SIZE

#define CHUNK_MOTOR_DATA_SIZE 2

//2^8
#define MESSAGE_MAX_SIZE 256 


namespace SDSP
{
	const static unsigned char headerValidation[] = { 0xA5, 0x5A, 0x69, 0x01 };

	union ByteUnion
	{
		unsigned long long b8;
		unsigned int b4[2];
		unsigned short b2[4];
		unsigned char b1[8];
	};


	struct Header
	{
		bool valid			{false};
		uint32_t length		{0};
	};

	struct ChunkMotorControl
	{
		const uint32_t length	{10}; // This will always be 10 with current structure. 4 + 4 + 2
		char type[CHUNK_TYPE_SIZE] {};
		uint16_t speed			{0}; // speed that the ESC will operate at. Motor will start at speed 1150, and can go above 2k
		bool isUsed				{false};
	};

	struct Chunk
	{
		uint32_t length		{0};
		char type[CHUNK_TYPE_SIZE] {};
		uint8_t * data 		{nullptr};
	};	

	enum Types
	{
		NA = 0,
		TOLM = 1,
		TORM,
		BOLM,
		BORM
	};
	static void getTypeString( SDSP::Types type, char * out )
	{
		uint8_t counter = 0;
		switch( type )
		{
			case SDSP::TOLM:
				out[ counter++ ] = 'T';
				out[ counter++ ] = 'O';
				out[ counter++ ] = 'L';
				out[ counter++ ] = 'M';
				return;
			case SDSP::TORM: return "TORM";
				out[ counter++ ] = 'T';
				out[ counter++ ] = 'O';
				out[ counter++ ] = 'R';
				out[ counter++ ] = 'M';
				return;	
			case SDSP::BOLM:
				out[ counter++ ] = 'B';
				out[ counter++ ] = 'O';
				out[ counter++ ] = 'L';
				out[ counter++ ] = 'M';
				return;
			case SDSP::BORM:
				out[ counter++ ] = 'B';
				out[ counter++ ] = 'O';
				out[ counter++ ] = 'R';
				out[ counter++ ] = 'M';
				return;
		}
	}


	struct Tangibles
	{
		Header header;
		SDSP::ChunkMotorControl chunkTOLM;
		SDSP::ChunkMotorControl chunkTORM;
		SDSP::ChunkMotorControl chunkBOLM;
		SDSP::ChunkMotorControl chunkBORM;
		Tangibles()
		{
			SDSP::getTypeString( SDSP::TOLM, chunkTOLM.type );
			SDSP::getTypeString( SDSP::TORM, chunkTORM.type );
			SDSP::getTypeString( SDSP::BOLM, chunkBOLM.type );
			SDSP::getTypeString( SDSP::BORM, chunkBORM.type );
		};
	};

	//assumption, the in param is 4 bytes
	static Types getTypeFromString( char * in )
	{
		Types res = NA;

		if( uti::compare( in, "TOLM" )) res = TOLM;
		else if( uti::compare( in, "TORM" )) res = TORM;
		else if( uti::compare( in, "BOLM" )) res = BOLM;
		else if( uti::compare( in, "BORM" )) res = BORM;


		return res;
	}

};

#endif // _SDSP_H_