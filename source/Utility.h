/**
 * Copyright (C) 2022-2022 theman1998 bigmaceater589@gmail.com
 * This file belongs to the Simple Drone Serial Protocol
 */

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

//utility scope
namespace uti
{
	void copy( const char * in, uint32_t size, char * out);
	void copy( const uint8_t * in, uint32_t size, uint8_t * out);
	bool compare( const uint8_t * in, const uint8_t * argument, uint32_t size = 0 );
}
#endif // _UTILITY_H_