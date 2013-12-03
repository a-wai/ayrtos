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

#include "task.h"
#include <avr/sleep.h>

extern int main(void);

void AYTaskInitList(void)
{
  uint8_t i;
  
  ayCurrentTask = 0;
  
  ayTaskList[0].id = 0;
  ayTaskList[0].sp = RAMEND;
  ayTaskList[0].func = main;
  ayTaskList[0].state = TASK_RUNNING;
  ayTaskList[0].priority = TASK_PRIORITY_STD;
  ayTaskList[0].waiting = 0;

  for (i = 1; i < MAX_TASKS; i++)
  {
    ayTaskList[i].id = -1;
    ayTaskList[i].state = TASK_NONE;
  }
}

int8_t AYTaskCreate(void (*func)(void))
{
  int8_t i;
  
  for (i = 1; i < MAX_TASKS; i++)
  {
    if (ayTaskList[i].id < 0)
    {
      ayTaskList[i].id = i;
      ayTaskList[i].sp = RAMEND - (i * STACK_SIZE);
      ayTaskList[i].func = func;
      ayTaskList[i].state = TASK_CREATED;
      ayTaskList[i].priority = TASK_PRIORITY_STD;
      ayTaskList[i].waiting = 0;
      
      break;
    }
  }
  
  if (i == MAX_TASKS)
    return -1;
  else
    return i;
}

void AYTaskEnd(int8_t task)
{
  ayTaskList[task].id = -1;
  ayTaskList[task].sp = 0;
}

void AYTaskWaitMs(int16_t cnt)
{
  cli();
  
  if (aySchedSleepCounts[ayCurrentTask].tid != ayCurrentTask)
  {
    aySchedSleepCounts[ayCurrentTask].tid = ayCurrentTask;
    aySchedSleepCounts[ayCurrentTask].count = cnt;
    
    ayTaskList[ayCurrentTask].state = TASK_BLOCKED;
  }  
  
  sei();

  asm volatile ("sleep\n\t");
}

// Task switching
ISR(TIMER0_COMPA_vect, ISR_NAKED)
{
  uint8_t pcl, pch, spl, sph;
  int8_t task;
  
  // Save context
  asm volatile (
    "push   r0             \n\t"    // r0
    "in     r0, __SREG__   \n\t"
    "push   r0             \n\t"    // SREG
    "push   r1             \n\t"    // r1
    "clr    r1             \n\t"    // GCC expects r1 to be null
    "push   r2             \n\t"    // r2
    "push   r3             \n\t"    // r3
    "push   r4             \n\t"    // r4
    "push   r5             \n\t"    // r5
    "push   r6             \n\t"    // r6
    "push   r7             \n\t"    // r7
    "push   r8             \n\t"    // r8
    "push   r9             \n\t"    // r9
    "push   r10            \n\t"    // r10
    "push   r11            \n\t"    // r11
    "push   r12            \n\t"    // r12
    "push   r13            \n\t"    // r13
    "push   r14            \n\t"    // r14
    "push   r15            \n\t"    // r15
    "push   r16            \n\t"    // r16
    "push   r17            \n\t"    // r17
    "push   r18            \n\t"    // r18
    "push   r19            \n\t"    // r19
    "push   r20            \n\t"    // r20
    "push   r21            \n\t"    // r21
    "push   r22            \n\t"    // r22
    "push   r23            \n\t"    // r23
    "push   r24            \n\t"    // r24
    "push   r25            \n\t"    // r25
    "push   r26            \n\t"    // r26
    "push   r27            \n\t"    // r27
    "push   r28            \n\t"    // r28
    "push   r29            \n\t"    // r29
    "push   r30            \n\t"    // r30
    "push   r31            \n\t"    // r31
    "in     %0, __SP_L__   \n\t"    // Save current Stack Pointer
    "in     %1, __SP_H__   \n\t"
    :"=r"(spl), "=r"(sph)
  );
  
  // Update the remaining delay for sleeping task and elect the task to be run
  AYSchedUpdateCounts();
  task = AYSchedSelectTask(ayCurrentTask);

  if (task != ayCurrentTask)
  {
    // Save the previous task SP
    ayTaskList[ayCurrentTask].sp = (sph << 8) + spl;
    
    // Mark the previous task as ready (only if previously running, a blocked task remains blocked !)    
    if (ayTaskList[ayCurrentTask].state == TASK_RUNNING)
      ayTaskList[ayCurrentTask].state = TASK_READY;

    // Prepare next task Stack Pointer    
    spl = (uint8_t) ayTaskList[task].sp;
    sph = (uint8_t) (ayTaskList[task].sp >> 8);

    // If task has never run yet, we have more things to do
    if (ayTaskList[task].state == TASK_CREATED)
    {
      // We need to put the Program Counter on a new stack and populate it
      pcl = (uint8_t) ayTaskList[task].func;
      pch = (uint8_t) ((uint16_t)ayTaskList[task].func >> 8);

      // Create a whole context for the new task
      asm volatile (
        "out    __SP_L__, %0   \n\t"
        "out    __SP_H__, %1   \n\t"
        "push   %2             \n\t"    // push PC_L first
        "push   %3             \n\t"    // push PC_H then
        "clr    r0             \n\t"
        "push   r0             \n\t"    // r0
        "in     r0, __SREG__   \n\t"
        "push   r0             \n\t"    // SREG
        "clr    r0             \n\t"
        "clr    r1             \n\t"    // GCC expects r1 to be null
        "push   r0             \n\t"    // r1
        "push   r0             \n\t"    // r2
        "push   r0             \n\t"    // r3
        "push   r0             \n\t"    // r4
        "push   r0             \n\t"    // r5
        "push   r0             \n\t"    // r6
        "push   r0             \n\t"    // r7
        "push   r0             \n\t"    // r8
        "push   r0             \n\t"    // r9
        "push   r0             \n\t"    // r10
        "push   r0             \n\t"    // r11
        "push   r0             \n\t"    // r12
        "push   r0             \n\t"    // r13
        "push   r0             \n\t"    // r14
        "push   r0             \n\t"    // r15
        "push   r0             \n\t"    // r16
        "push   r0             \n\t"    // r17
        "push   r0             \n\t"    // r18
        "push   r0             \n\t"    // r19
        "push   r0             \n\t"    // r20
        "push   r0             \n\t"    // r21
        "push   r0             \n\t"    // r22
        "push   r0             \n\t"    // r23
        "push   r0             \n\t"    // r24
        "push   r0             \n\t"    // r25
        "push   r0             \n\t"    // r26
        "push   r0             \n\t"    // r27
        "push   r0             \n\t"    // r28
        "push   r0             \n\t"    // r29
        "push   r0             \n\t"    // r30
        "push   r0             \n\t"    // r31
        ::"r"(spl), "r"(sph), "r"(pcl), "r"(pch)
      );
    }
    else // Task has already run, we only need to change the SP
    {
      // Restore saved SP
      asm volatile (
        "out    __SP_L__, %0   \n\t"
        "out    __SP_H__, %1   \n\t"
        ::"r"(spl), "r"(sph)
      );
    }

    // Set new task as current
    ayCurrentTask = task;
    ayTaskList[ayCurrentTask].state = TASK_RUNNING;
  }
  
  // Restore context
  asm volatile (
    "pop    r31            \n\t"    // r31
    "pop    r30            \n\t"    // r30
    "pop    r29            \n\t"    // r29
    "pop    r28            \n\t"    // r28
    "pop    r27            \n\t"    // r27
    "pop    r26            \n\t"    // r26
    "pop    r25            \n\t"    // r25
    "pop    r24            \n\t"    // r24
    "pop    r23            \n\t"    // r23
    "pop    r22            \n\t"    // r22
    "pop    r21            \n\t"    // r21
    "pop    r20            \n\t"    // r20
    "pop    r19            \n\t"    // r19
    "pop    r18            \n\t"    // r18
    "pop    r17            \n\t"    // r17
    "pop    r16            \n\t"    // r16
    "pop    r15            \n\t"    // r15
    "pop    r14            \n\t"    // r14
    "pop    r13            \n\t"    // r13
    "pop    r12            \n\t"    // r12
    "pop    r11            \n\t"    // r11
    "pop    r10            \n\t"    // r10
    "pop    r9             \n\t"    // r9
    "pop    r8             \n\t"    // r8
    "pop    r7             \n\t"    // r7
    "pop    r6             \n\t"    // r6
    "pop    r5             \n\t"    // r5
    "pop    r4             \n\t"    // r4
    "pop    r3             \n\t"    // r3
    "pop    r2             \n\t"    // r2
    "pop    r1             \n\t"    // r1
    "pop    r0             \n\t"    // SREG
    "out    __SREG__, r0   \n\t"
    "pop    r0             \n\t"    // r0
    "reti                  \n\t"    // Return from interrupt
  );
}
