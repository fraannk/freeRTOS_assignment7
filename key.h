/*
 * key.c
 *
 *  Created on: 28. apr. 2017
 *      Author: fraannk
 */

#ifndef _KEY_H
  #define _KEY_H

#include "emp_type.h"
#include "FreeRTOS.h"
#include "queue.h"

void readKey(void *p);
void initKeyboard();

extern xQueueHandle scale_queue;
extern char offset_value;
extern char scale_value;

#endif
