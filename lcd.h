/*
 * lcd.h
 *
 *  Created on: 25 Apr 2017
 *      Author: fraannk
 */

#ifndef LCD_H_
#define LCD_H_

/***************************** Include files *******************************/
#include "emp_type.h"
#include "FreeRTOS.h"
#include "queue.h"

extern xQueueHandle queue;

void initLCD();
void dispLCD(void *p);
void delay();
void LCD_write_data(INT8U byte);
void setCursor(INT8U col, INT8U row);
void clearLCD();

#endif
