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

#ifndef __AY_TASK_H
#define __AY_TASK_H

#include "kernel/kernel.h"

#define STACK_SIZE 128

#define TASK_NONE    -1
#define TASK_CREATED  0
#define TASK_READY    1
#define TASK_BLOCKED  2
#define TASK_RUNNING  3

//#define RT_TICK   1000 // Switch tasks every 1000µs

typedef enum {
  TASK_PRIORITY_STD = 0,
  TASK_PRIORITY_HIGH
} ay_task_priority_t;

// Task base structure
typedef struct ay_task {
  int8_t id;                    // Task ID
  uint16_t sp;                  // Stack Pointer value
  void (*func)(void);           // Main function (used to set PC on first call)
  int8_t state;                 // State (created, running, blocked, etc...)
  ay_task_priority_t priority;  // Priority
  int8_t waiting;               // Waiting time when high priority
} ay_task_t;

void AYTaskInitList(void);
int8_t AYTaskCreate(void (*func)(void));
void AYTaskEnd(int8_t task);
void AYTaskWait(void);
void AYTaskWaitMs(int16_t);

// List of all the tasks
ay_task_t ayTaskList[MAX_TASKS];
// ID of the current running task
int8_t ayCurrentTask;

#endif
