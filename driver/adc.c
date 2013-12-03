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

#include "adc.h"

// Init the serial interface
void AYAdcInit(uint8_t source)
{
#ifdef ATMEGA328P
  AYAdcInit_AT328P(source);
#else
#error "ATMEGA328P not defined !"
#endif	
}

uint16_t AYAdcRead(void)
{
#ifdef ATMEGA328P
  return AYAdcRead_AT328P();
#else
#error "ATMEGA328P not defined !"
#endif	
}
