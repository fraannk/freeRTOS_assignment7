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

/*****************************    Defines    *******************************/
#define     LCD_CHARS               16
#define     LCD_LINES               2
#define     LCD_BUF_SIZE            LCD_CHARS*LCD_LINES

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void initLCD();
void lcd_write_line(INT8U line[]);
void lcd_write_data(INT8U byte);
void lcd_set_cursor(INT8U x, INT8U y);
void lcd_write_buffer(INT8U *buffer);
void delay_us(INT32U time);

void dispLCD(void *p);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Display stuff on LCD
******************************************************************************/


/****************************** End Of Module *******************************/

#endif /* LCD_H_ */
