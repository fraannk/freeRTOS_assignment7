/*
 * lcd.c
 *
 *  Created on: 25 Apr 2017
 *      Author: fraannk
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "emp_type.h"

/*****************************    Defines    *******************************/
#define     LCD_DATA_PORT           GPIO_PORTC_DATA_R
#define     LCD_DATA_DDR            GPIO_PORTC_DIR_R
#define     LCD_DATA_EN             GPIO_PORTC_DEN_R
#define     LCD_D4_PIN              4
#define     LCD_D5_PIN              5
#define     LCD_D6_PIN              6
#define     LCD_D7_PIN              7

#define     LCD_CTRL_PORT           GPIO_PORTD_DATA_R
#define     LCD_CTRL_DDR            GPIO_PORTD_DIR_R
#define     LCD_CTRL_EN             GPIO_PORTD_DEN_R
#define     LCD_RS_PIN              2
#define     LCD_E_PIN               3
/*****************************   Constants   *******************************/
typedef enum {HIGH, LOW} pin_state;

void delay(){
    int i;
    for(i = 0; i<=10000; i++)
        i;
}

void lcd_write_nibble(INT8U byte)
{

  LCD_CTRL_PORT &= ~(1<<LCD_E_PIN);

  // clear all data bits
  LCD_DATA_PORT &= ~( 1<<LCD_D7_PIN );
  LCD_DATA_PORT &= ~( 1<<LCD_D6_PIN );
  LCD_DATA_PORT &= ~( 1<<LCD_D5_PIN );
  LCD_DATA_PORT &= ~( 1<<LCD_D4_PIN );

  // put Upper Nipple of byte on the data port
  LCD_DATA_PORT |= (byte & 1<<7 ) ? (1<<LCD_D7_PIN) : 0;
  LCD_DATA_PORT |= (byte & 1<<6 ) ? (1<<LCD_D6_PIN) : 0;
  LCD_DATA_PORT |= (byte & 1<<5 ) ? (1<<LCD_D5_PIN) : 0;
  LCD_DATA_PORT |= (byte & 1<<4 ) ? (1<<LCD_D4_PIN) : 0;
  delay();



  LCD_CTRL_PORT |= 1<<LCD_E_PIN;


  LCD_CTRL_PORT &= ~(1<<LCD_E_PIN);

}

void lcd_write_instruction(INT8U byte)
{
  LCD_CTRL_PORT &= ~(1<<LCD_RS_PIN);
  LCD_CTRL_PORT &= ~(1<<LCD_E_PIN);
  lcd_write_nibble(byte);
  lcd_write_nibble(byte<<4);
  delay();
}

LCD_write_data(INT8U byte){
    LCD_CTRL_PORT |= (1<<LCD_RS_PIN);
    LCD_CTRL_PORT &= ~(1<<LCD_E_PIN);
    lcd_write_nibble(byte);
    lcd_write_nibble(byte<<4);

    delay();
}

void initLCD(){


    // Set GPIOF on Run Mode Clock Gating Control Register PORTC 6 PORTD
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2 | SYSCTL_RCGCGPIO_R3;

    // Init GPIO pins for LCD display

    GPIO_PORTC_DIR_R |= 0b11110000; //D4-D7 output

    GPIO_PORTC_DEN_R  |= 0b11110000; //D4-D7 Digital


    GPIO_PORTD_DIR_R |= 0b1100; // RS and E outputs

    GPIO_PORTD_DEN_R  |= 0b1100; // RS and E Digital enable

    LCD_CTRL_PORT = 0x00; // RS and E low
    LCD_DATA_PORT = 0x30; // set DB4 and DB5 high
    delay();

    LCD_CTRL_PORT = 0x00; // RS and E low
    LCD_DATA_PORT = 0x30; // set DB4 and DB5 high
    delay();

    LCD_CTRL_PORT = 0x00; // RS and E low
    LCD_DATA_PORT = 0x30; // set DB4 and DB5 high

    delay();

    //Function set

    lcd_write_nibble(0x20);
    delay();
    lcd_write_instruction(0b00101000);
    lcd_write_instruction(0b00001000);
    lcd_write_instruction(0x01);
    delay();
    lcd_write_instruction(0b00000110);
    lcd_write_instruction(0b00001100);

}

void dispLCD(void *p) {
    while(1) {
        int k;

        for(k=0b00; k<11111111;k++){
            delay();

            LCD_write_data(k);
        }
    }
}
