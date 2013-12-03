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

#include "timer.h"

void AYTickInit_AT328P(uint16_t tick)
{
    // Init Timer0 (RT tick)

    TCCR0A = 0x00;
    TCCR0A |= _BV(WGM01);
    TCCR0B = 0x00;
    TCCR0B |= _BV(CS01) | _BV(CS00); // Prescaling /64 (count every 4µs)
    TIMSK0 = 0x00;
    TIMSK0 |= _BV(OCIE0A); // Allow OCR0A
    TCNT0 = 0x00;
    OCR0A = tick / 4; // Set scheduling tick value
}

void AYCounterInit_AT328P(void)
{
    // Init Counter1 (time count)
    
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCCR1B |= _BV(CS11); // Prescaling /8 (count every 0,5µs)
    TCCR1C = 0x00;
    TIMSK1 = 0x00;
    TCNT1 = 0x00;
}

uint16_t AYGetMicros_AT328P(void)
{
    return TCNT1 / 2; // Counter1 counts every 0,5µs => 1 ms = 2 counts !!!
}
