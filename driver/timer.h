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

#ifndef __AY_TIMER_H
#define __AY_TIMER_H

#include "kernel/kernel.h"
#include "util/str.h"
#include "arch/avr/atmega328p/timer.h"

void AYTickInit(uint16_t);
void AYCounterInit(void);
uint16_t AYGetMicros(void);

#endif
