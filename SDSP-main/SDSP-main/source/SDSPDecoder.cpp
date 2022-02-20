#include "SDSPDecoder.h"


SDSPDecoder::SDSPDecoder( const uint8_t * data, uint32_t size ) : messageP{ new uint8_t[size] }, messageSize{ size }
{
	if ( size > 0 )
	{
		copy( data, size, messageP );
	}
}

SDSPDecoder::SDSPDecoder( const String message ) : messageP{ nullptr }, messageSize{ 0 }
{
	if( message.length() != 0 )
	{
		messageP = new uint8_t[ message.length() ];
		messageSize = message.length();
		uint8_t * p = ( uint8_t * ) message.c_str();
		copy( p, messageSize, messageP );
	}
}

SDSPDecoder::~SDSPDecoder()
{
	if( messageP != nullptr )
	{
		delete [] messageP;
	}
}


void SDSPDecoder::insertMessage( String message )
{
	if( message.length() == 0 )
	{
    Serial.println("Message of length: 0"); 
		return;
   
    /* I let the serial monitor run for a bit (~5mins) 
     * and for some reason this print started calling, 
     * possible error in the future? 
    */
	}
	if( messageP != nullptr )
	{
		delete [] messageP;
	}

	messageP = new uint8_t[ message.length() ];
	messageSize = message.length();
	uint8_t * p = ( uint8_t * ) message.c_str();
	copy( p, messageSize, messageP );
}

void SDSPDecoder::insertMessage( uint8_t * data, uint32_t size )
{
	if( size == 0 )
	{
		return;
	}
	if( messageP != nullptr )
	{
		delete [] messageP;
	}
	messageP = new uint8_t[size];
	copy( data, size, messageP );
}

void SDSPDecoder::parse()
{
	bool thisProtocol = checkHeader();
	if ( ! thisProtocol )
	{
		Serial.println( "Failure in Protocal Validation" );
		return;
	}
  
 //Serial.println( messageP.length );
}


bool SDSPDecoder::checkHeader( const uint8_t * data )
{
	uint8_t * headerP  = ( uint8_t * ) data;
	if( data == nullptr )
	{
		headerP = messageP;
	}

	uint32_t byte = 0;

	for( byte; byte < sizeof( SDSP::headerValidation ); byte++ )
	{
		if( headerP[ byte ] != SDSP::headerValidation[ byte ] )
		{
      Serial.println(( "Header Validation Failed:" ));
      Serial.print(( SDSP::headerValidation[byte],HEX ));
      Serial.print((" "));
      Serial.print(( headerP[byte],HEX ));
      Serial.print((" "));
      Serial.println(byte);
      
			container.header.valid = false;
			return false;
		}
	}

	union SDSP::ByteUnion bUnion;

	for ( int i = 0; i < MESSAGE_LENGTH; i++ )
	{
		bUnion.b1[ 3 - i ] = headerP[ byte++ ];
	}

	container.header.length = bUnion.b4[1];
	//Serial.println(bUnion.b4[3]);
  //Serial.println(sizeof(headerP));
	return true;
}
