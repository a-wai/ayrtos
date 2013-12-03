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

#include "str.h"

uint8_t AYStrlen(char *str)
{
  int i = 0;
  
  while (str[i] != 0)
    i++;
    
  return i;
}

uint8_t AYStreq(char *str1, char *str2)
{
  uint8_t len1, len2, i;
  
  len1 = AYStrlen(str1);
  len2 = AYStrlen(str2);
  
  if (len1 != len2)
    return 0;
  
  for (i = 0; i < len1; i++)
    if (str1[i] != str2[i])
      return 0;
      
  return 1;
}
