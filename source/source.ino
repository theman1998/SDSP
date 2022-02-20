#include "SDSPEncoder.h"
#include "SDSPDecoder.h"

SDSPEncoder encoder;
SDSPDecoder decoder;


void setup() 
{
	Serial.begin( 9600 );

}


void loop()
{
	encoder.insertMotorControl( 100, SDSP::TOLM );
	encoder.packer();
	uint8_t * encodedMessage = nullptr;
	uint32_t encodedSize = encoder.getPackSize();
	encodedMessage = new uint8_t[encodedSize];
	encoder.getPackMessage( encodedMessage );

	
	Serial.print( encodedSize );
	Serial.print( " string[0-7]: ");
	for( int i = 0; i < encodedSize; i++ )
	{
	Serial.print( (uint8_t)encodedMessage[i], HEX );
	Serial.print( " " );
	}
	Serial.println( " " );
	

	decoder.insertMessage( encodedMessage, encodedSize );
	decoder.parse();

	delete [] encodedMessage;
	delay( 2000 );
}
