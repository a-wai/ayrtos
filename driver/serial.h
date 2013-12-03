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

#ifndef __AY_SERIAL_H
#define __AY_SERIAL_H

#include "kernel/kernel.h"
#include "util/str.h"
#include "arch/avr/atmega328p/usart.h"

void AYSerialInit(uint32_t);

void AYSerialReceive(char *);
void AYSerialSend(char);

void AYSerialString(char *);
void AYSerialInt(uint16_t);
void AYSerialHex(uint16_t);

#endif
