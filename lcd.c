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
#include "FreeRTOS.h"
#include "queue.h"

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

void delay(){
    int i;
    for(i = 0; i<=10000; i++){}
        //i;
}

void lcd_write_nibble(INT8U byte){
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

void lcd_write_instruction(INT8U byte){
  LCD_CTRL_PORT &= ~(1<<LCD_RS_PIN);
  LCD_CTRL_PORT &= ~(1<<LCD_E_PIN);
  lcd_write_nibble(byte);
  lcd_write_nibble(byte<<4);
  delay();
}

void LCD_write_data(INT8U byte){
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

    value_text();

}

void clearLCD(void){
  lcd_write_instruction(0x01);
  delay();
}

void setCursor(INT8U x, INT8U y){
  INT8U adr = 0x80;
  adr |= (y*0x40 + x);
  lcd_write_instruction(adr);
}

void dispLCD(void *p){
    int prev_number = 0;
    char offset_value = '0';
    char scale_value = '0';

    while(1){
        xQueueReceive(adc_queue, &rx_adc, 5);
        char conv[] = {' ',' ',' ',' '};
        char_conv(rx_adc, conv);

        setCursor(4,0);
        for(int i = 0; i < (sizeof(conv)); i++){
            LCD_write_data(conv[i]);
        }
        xQueueReceive(scale_queue, &rx_scale, 5);
        if(rx_scale == '#') {
            setCursor(9, 1);
            LCD_write_data(prev_number);
            scale_value = prev_number;
        } else if (rx_scale == '*'){
            setCursor(15, 0);
            LCD_write_data(prev_number);
            offset_value = prev_number;
        } else {
            prev_number = rx_scale;
        }

        int offset = offset_value - '0';
        int scale = scale_value - '0';
        uint32_t final_value = (rx_adc * scale) + offset;

        char conv2[] = {' ',' ',' ',' ',' ',' '};
        char_conv(final_value, conv2);
        setCursor(11,1);
        for(int i = 0; i < (sizeof(conv2)); i++){
            LCD_write_data(conv2[i]);
        }
    }
}

void value_text() {
    char ai_text[] = {'A', 'I', ':', ' '};
    setCursor(0,0);
    for(int i = 0; i < sizeof(ai_text); i++){
        LCD_write_data(ai_text[i]);
    }

    char scaled_text[] = {'S', 'c', 'a', 'l', 'e', 'd', ':', ' ', '#', '0'};
    setCursor(0,1);
    for(int i = 0; i < sizeof(scaled_text); i++){
        LCD_write_data(scaled_text[i]);
    }

    char offset_text[] = {'O', 'f', 'f', '.' , ' ', '*', '0'};
    setCursor(9,0);
    for(int i = 0; i < sizeof(offset_text); i++){
        LCD_write_data(offset_text[i]);
    }
}

char* char_conv(int i, char str[]){
    char* p = str;
    int move = i;
    do {
        ++p;
        move = move/10;
    } while(move);

    *p = ' ';
    do{
        *--p = '0' + (i % 10);
        i = i/10;
    } while(i);
    return str;
}
