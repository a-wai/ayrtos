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

#include "sample.h"

void LedBlink1()
{
  while(1)
  {
    // Blink LED every 1s
    PORT_DIG2 |= _BV(PIN_D8);
    AYTaskWaitMs(500);
    PORT_DIG2 &= ~_BV(PIN_D8);
    AYTaskWaitMs(500);
  }
}

void LedBlink2()
{
  while(1)
  {  
    // Clear screen every 2s
    PORT_DIG2 |= _BV(PIN_D9);
    AYTaskWaitMs(1000);
    PORT_DIG2 &= ~_BV(PIN_D9);
    AYTaskWaitMs(1000);
  }
}

void SerialEcho()
{
  char c;

  while(1)
  {
    // Echo each character received from the serial line
    AYSerialReceive(&c);
    AYSerialString("Received \"");
    AYSerialSend(c);
    AYSerialString("\"\n\r");
    
    // If we received '&', echo the current ADC value
    if (c == '&')
    {
      AYSerialString("ADC value : ");
      AYSerialInt(AYAdcRead());
      AYSerialString("\n\r");
    }
  }
}

void AYAppInit()
{
  // Init serial interface
  AYSerialInit(9600);
  
  // Set pins 9 to 13 as outputs
  DDR_DIG2 |= _BV(PIN_D13) | _BV(PIN_D12) | _BV(PIN_D11) | _BV(PIN_D10) | _BV(PIN_D8) | _BV(PIN_D9);

  // Populate task list
  AYTaskCreate(LedBlink1);
  AYTaskCreate(LedBlink2);
  AYTaskCreate(SerialEcho);
  
  // Init ADC on pin A0
  AYAdcInit(PIN_A0);
}
