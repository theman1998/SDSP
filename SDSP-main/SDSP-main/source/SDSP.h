#ifndef _SDSP_H_
#define _SDSP_H_

#define HEADER_SIZE 8
#define MESSAGE_LENGTH 4


namespace SDSP
{
	static const unsigned char headerValidation[] = { (unsigned char)0xA5, (unsigned char)0x5A, (unsigned char)0x69, (unsigned char)0x01 };

	union ByteUnion
	{
		unsigned long long b8;
		unsigned int b4[2];
		unsigned short b2[5];
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
		String type				{""};
		uint16_t speed			{0}; // speed that the ESC will operate at. Motor will start at speed 1150, and can go above 2k
		bool isUsed				{false};
	};

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



	struct Tangibles
	{
		Header header;
		SDSP::ChunkMotorControl chunkTOLM;
		SDSP::ChunkMotorControl chunkTORM;
		SDSP::ChunkMotorControl chunkBOLM;
		SDSP::ChunkMotorControl chunkBORM;
	};


	static const String getTypeString( SDSP::Types type )
	{
		switch( type )
		{
			case SDSP::TOLM: return "TOLM";
			case SDSP::TORM: return "TORM";
			case SDSP::BOLM: return "BOLM";
			case SDSP::BORM: return "BORM";
		}
		return "";
	}



};

#endif // _SDSP_H_
