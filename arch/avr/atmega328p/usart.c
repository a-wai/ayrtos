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

#include "usart.h"

void AYSerialInit_AT328P(uint32_t br)
{
	uint16_t ubrr;
	
  // Calculate baud rate (using /16 prescaler for the 16MHz Arduino clock)
  ubrr = F_CPU / (16 * br) - 1;
  UBRR0H = (uint8_t) (ubrr >> 8);
  UBRR0L = (uint8_t) ubrr;
	
  // Disable Double Speed & Multi Processor Communication
  UCSR0A &= ~(_BV(U2X0) | _BV(MPCM0));
  // Disable USART0 interrupts & clear UCSZ02 (8-bit transmission)
  UCSR0B &= ~(_BV(RXCIE0) | _BV(TXCIE0) | _BV(UDRIE0) | _BV(UCSZ02));
  // Enable USART0 & RX complete interrupt
  UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
  // Set asynchronous link, no parity bit, 1 stop bit
  UCSR0C &= ~(_BV(UMSEL01) | _BV(UMSEL00) | _BV(UPM01) | _BV(UPM00) | _BV(USBS0));
  // Set 8 data bits
  UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}

void AYSerialReceive_AT328P(char *c)
{
  // Wait for the "RX complete" flag, indicating data has been received
  while (!(UCSR0A & _BV(RXC0)));
  
  // Read the received data
  *c = UDR0;
}

void AYSerialSend_AT328P(char c)
{
  // Wait for the "UDR empty" flag, indicating data register is empty
  // and ready to be filled with data to transmit
  while (!(UCSR0A & _BV(UDRE0)));
  
  // Write the data to transmit into data register (acts as transmit buffer)
  UDR0 = c;
}
