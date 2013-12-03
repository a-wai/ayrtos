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

#include "kernel.h"

extern void AYAppInit(void);

int main (void)
{
  // Disable watchdog timer in case the CPU is rebooting after a WDT interrupt
  wdt_disable();
  cli();
  
  // Init MCU : set flags needed for proper OS operation
  AYMcuInit();
  
  // *** Init major OS functions ***

  // Scheduler
  AYSchedInit();  
  // RT Tick counter and interrupt
  AYTickInit(RT_TICK);
  // Time counter (used for AYGetMicros)
  AYCounterInit();


  // Init App : set flags needed for user applications (function written by end user)
  AYAppInit();

  sei();
  
  while (1)
    asm volatile ("sleep\n\t");
    
  return 0;
}
