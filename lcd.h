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
#include <stdint.h>
#include "tm4c123gh6pm.h"

extern xQueueHandle adc_queue;
uint32_t rx_adc;

extern xQueueHandle scale_queue;
char rx_scale;

void initLCD();
void dispLCD(void *p);
void delay();
void LCD_write_data(INT8U byte);
void setCursor(INT8U col, INT8U row);
void clearLCD();
void LCD_write_buffer(INT8U *buffer);
void LCD_write_line(INT8U line[]);
void value_text();
char* char_conv(int i, char str[]);

#endif
