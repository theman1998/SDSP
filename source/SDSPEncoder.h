#ifndef _SDSPENCODER_H_
#define _SDSPENCODER_H_

#include <iostream>
#include <string>

/**
 * Simple Drone Serial Protocol Encoder will encode and decode messages. 
 */
class SDSPEncoder
{
public:
	SDSPEncoder( const uint8_t * data = nullptr, uint32_t size = 0 );
	SDSPEncoder( const std::string message );
	~SDSPEncoder();

	void insertMessage( std::string message );
	void insertMessage( uint8_t * data, uint32_t size );

	struct Header
	{
		bool valid			{false};
		uint32_t length		{0};
	};
	struct Chunk
	{
		uint32_t length		{0};
		std::string type	{""};
		uint8_t * data 		{nullptr};
	};

private:
	uint8_t * messageP;
	uint32_t messageSize;
};


#endif // _SDSPENCODER_H_