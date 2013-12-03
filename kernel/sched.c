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

#include "sched.h"

// Select task to be run according to scheduling policy
// The policy is based on a round-robin with simple priority management :
//  * A task that wakes up (sleep delay elapsed) has high priority
//  * A task waiting for an interrupt gets high priority once the interrupt occurs
//  * A task with high priority keeps that priority until it's elected
//  * All other tasks are standard priority, and will be elected only if there's no high priority task

int8_t AYSchedSelectTask(int8_t current)
{
  int8_t new, task, i, hitid, highest;
  
  new = highest = hitid = -1;
  task = current;
  
  // Check if there is a high priority task to activate
  for (i = 0; i < MAX_TASKS; i++)
  {
    if (ayTaskList[i].state == TASK_READY && ayTaskList[i].priority == TASK_PRIORITY_HIGH)
    {
      // Check if no other high priority task has been waiting for a longer time
      if (ayTaskList[i].waiting > highest)
      {
        highest = ayTaskList[i].waiting;
        hitid = i;
      }
      // Increase waiting time for this task
      ayTaskList[i].waiting++;
    }
  }
  
  if (hitid >= 0)
  {
    // If there's an elected task, we reset its priority and waiting time to 0
    new = hitid;
    ayTaskList[new].priority = TASK_PRIORITY_STD;
    ayTaskList[new].waiting = 0;
  }
  
 // If no task has been elected so far (new == -1) wake up the next ready task
  while (new < 0)
  {
    if (task == (MAX_TASKS - 1))
      task = 0;
    else
      task++;
      
    // Check if task is ready
    if (ayTaskList[task].state == TASK_READY || ayTaskList[task].state == TASK_CREATED || ayTaskList[task].state == TASK_RUNNING)
      new = task;
    else if (new < 0 && (task == current))
      new = 0;
  }

  return new;
}

// Check if sleeping tasks should be woken up
void AYSchedUpdateCounts(void)
{
  int8_t i;
    
  for (i = 0; i < MAX_TASKS; i++)
  {
    // Check the task exists and it has set a sleep counter
    if (ayTaskList[i].id >= 0 && aySchedSleepCounts[i].tid == i)
    {
      aySchedSleepCounts[i].count -= 1; // Each tick is 1ms, should be based on RT_TICK duration
      
      // If the delay has elapsed, de-init the counter and make it high priority
      if (aySchedSleepCounts[i].count <= 0)
      {
        aySchedSleepCounts[i].tid = -1;
        ayTaskList[i].state = TASK_READY;
        ayTaskList[i].priority = TASK_PRIORITY_HIGH;
      }
    }
  }
}

// Init the scheduler structures
void AYSchedInit(void)
{
  int8_t i;
  
  // Init task list
  AYTaskInitList();

  for (i = 0; i < MAX_TASKS; i++)
  {
    aySchedSleepCounts[i].tid = -1;
    aySchedSleepCounts[i].count = 0;
  }  
}
