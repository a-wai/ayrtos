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

#include "pins.h"
#include "adc.h"

void AYAdcSelectSource_AT328P(uint8_t pin)
{
  // Sets the MUX3..0 bits of ADMUX accordingly with the selected source
  // See ATMega328P datasheet for details
  switch(pin)
  {
    case PIN_A0:
      ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
      break;
    case PIN_A1:
      ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1));
      ADMUX |= _BV(MUX0);
      break;
    case PIN_A2:
      ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX0));
      ADMUX |= _BV(MUX1);
      break;
    case PIN_A3:
      ADMUX &= ~(_BV(MUX3) | _BV(MUX2));
      ADMUX |= _BV(MUX1) | _BV(MUX0);
      break;
    case PIN_A4:
      ADMUX &= ~(_BV(MUX3) | _BV(MUX1) | _BV(MUX0));
      ADMUX |= _BV(MUX2);
      break;
    case PIN_A5:
      ADMUX &= ~(_BV(MUX3) | _BV(MUX1));
      ADMUX |= _BV(MUX2) | _BV(MUX0);
      break;
    default:
      break;
  }
}

void AYAdcInit_AT328P(uint8_t adPin)
{
  // Init all ADC registers
  ADMUX = ADCSRB = ADCSRA = 0;
  
  // Disable digital registers for PORTC
  DIDR0 = 0x3F;
  // Set voltage reference to Vcc (REFS0)
  ADMUX |= _BV(REFS0);
  // Select ADC ource pin
  AYAdcSelectSource_AT328P(adPin);
  // Enable ADC and start conversion (1st one takes longer) - Prescaler setting /8
  ADCSRA |= _BV(ADEN) | _BV(ADSC) | _BV(ADPS1) | _BV(ADPS0);
  // Set ADC to free running mode
  ADCSRB |= 0;
}

uint16_t AYAdcRead_AT328P(void)
{
  uint16_t value = 0;
  
  // Start ADC conversion
  ADCSRA |= _BV(ADSC);
  
  // Wait for conversion to finish  
  while (ADCSRA & _BV(ADSC));
  
  // Check the interrupt flag to see if the conversion has been completed
  if (ADCSRA & _BV(ADIF))
  {
    // Clear interrupt flag (should be cleared by ISR, but we're not using interrupts...)
    ADCSRA |= _BV(ADIF);
    // Read value
    // Value is stored on 10 bits : 2 MSB in ADCH, 8 LSB in ADCL
    value = ADCH * 256;
    value += ADCL;
  }

  return value;
}
