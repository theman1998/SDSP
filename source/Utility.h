#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Arduino.h>

void copy( const char * in, uint32_t size, char * out);
void copy( const uint8_t * in, uint32_t size, uint8_t * out);

#endif // _UTILITY_H_