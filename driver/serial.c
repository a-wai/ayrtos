/*
 * Copyright (C) 2013 Arnaud Ferraris.
 *
 * This file is part of AyRTOS.
 *
 * AyRTOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * AyRTOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with AyRTOS.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "serial.h"

// Init the serial interface
void AYSerialInit(uint32_t br)
{
  // Disable interrupts
  cli();

#ifdef ATMEGA328P
  AYSerialInit_AT328P(br);
#else
#error "ATMEGA328P not defined !"
#endif	
	
  // Restore interrupts
  sei();
}

// Wait for character reception and retrieve its value
void AYSerialReceive(char *c)
{
  // Wait for incoming serial data
#ifdef ATMEGA328P
  AYSerialReceive_AT328P(c);
#else
#error "ATMEGA328P not defined !"
#endif
}

// Send a character
void AYSerialSend(char c)
{
  // Wait for transmit buffer to be empty
#ifdef ATMEGA328P
  AYSerialSend_AT328P(c);
#else
#error "ATMEGA328P not defined !"
#endif
}

// Send a string over the serial line
void AYSerialString(char *str)
{
  uint8_t len, i;
 
  len = AYStrlen(str);
  
  for (i = 0; i < len; i++)
  {
    AYSerialSend(str[i]); // Send a character
  }
}

// Calculate integer powers
uint16_t ipow(uint16_t num, uint16_t pow)
{
  uint16_t result;
  
  result = 1;
  
  while (pow > 0)
  {
    result *= num;
    pow--;
  }
    
  return result;
}

// Print an integer on the serial console
void AYSerialInt(uint16_t num)
{
  uint16_t i, quo, flag;

  flag = 0;

  for(i = 4; i > 0; i--)
  {
    quo = num / ipow(10, i);
    num -= quo * ipow(10, i);

    if (!flag && quo)
      flag = 1;

    if (quo || flag)
    {
      AYSerialSend((char)(quo + 48));
    }
  }
  AYSerialSend((char)(num + 48));
}

// Send a 16-bit integer, printed in Hex form ("0x****")
void AYSerialHex(uint16_t num)
{
  uint16_t i, quo;

  AYSerialString("0x");
  
  for(i = 3; i > 0; i--)
  {
    quo = num / ipow(16, i);
    num -= quo * ipow(16, i);

    AYSerialSend((char)(quo + (quo < 10 ? 48 : 55)));
  }
  AYSerialSend((char)(num + (num < 10 ? 48 : 55)));
}
