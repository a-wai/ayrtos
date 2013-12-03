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

#ifndef __AY_KERNEL_H
#define __AY_KERNEL_H

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <avr/wdt.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef ATMEGA328P
    #include "arch/avr/atmega328p/pins.h"
#endif

#define MAX_TASKS 4
#define RT_TICK 1000 // in µs

#include "kernel/sched.h"
#include "kernel/task.h"
#include "driver/adc.h"
#include "driver/mcu.h"
#include "driver/serial.h"
#include "driver/timer.h"
#include "util/str.h"

#endif
