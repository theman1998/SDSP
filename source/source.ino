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
	String encodedMessage = encoder.getPackMessage();

	decoder.insertMessage( encodedMessage );
	decoder.parse();

	delay( 3000 );
}
