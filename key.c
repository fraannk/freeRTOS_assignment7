/*
 * key.c
 *
 *  Created on: 28. apr. 2017
 *      Author: simon
 */

#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include <stdint.h>
#include "key.h"

void initKeyboard(){
    GPIO_PORTE_DIR_R = 0x00; // make KEY H G J K inputs by clearing bits
    GPIO_PORTA_DIR_R = 0b00011100; // make KEY E F D output by setting bits
    GPIO_PORTE_DEN_R = 0b00001111; // Digital enable KEY H G J K
    GPIO_PORTA_DEN_R = 0b00011100; // Digital enable KEY D E F
}


void readKey(void *p){
    char button_pressed;
    while(1) {
        GPIO_PORTA_DATA_R = 0b000010000; // A logic high signal is given to col1-col3
        if((GPIO_PORTA_DATA_R == 0b000010000) && (GPIO_PORTE_DATA_R == 0b00001000) ){
            button_pressed = '1';
        }
        if((GPIO_PORTA_DATA_R == 0b000010000) && (GPIO_PORTE_DATA_R == 0b00000100) ){
            button_pressed = '4';
        }
        if((GPIO_PORTA_DATA_R == 0b000010000) && (GPIO_PORTE_DATA_R == 0b00000010) ){
            button_pressed = '7';
        }
        if((GPIO_PORTA_DATA_R == 0b000010000) && (GPIO_PORTE_DATA_R == 0b00000001) ){
            button_pressed = '*';
        }

        GPIO_PORTA_DATA_R = 0b000001000; // A logic high signal is given to col1-col3
        if((GPIO_PORTA_DATA_R == 0b000001000) && (GPIO_PORTE_DATA_R == 0b00001000) ){
            button_pressed = '2';
        }
        if((GPIO_PORTA_DATA_R == 0b000001000) && (GPIO_PORTE_DATA_R == 0b00000100) ){
            button_pressed = '5';
        }
        if((GPIO_PORTA_DATA_R == 0b000001000) && (GPIO_PORTE_DATA_R == 0b00000010) ){
            button_pressed = '8';
        }
        if((GPIO_PORTA_DATA_R == 0b000001000) && (GPIO_PORTE_DATA_R == 0b00000001) ){
            button_pressed = '0';
        }

        GPIO_PORTA_DATA_R = 0b000000100; // A logic high signal is given to col1-col3
        if((GPIO_PORTA_DATA_R == 0b000000100) && (GPIO_PORTE_DATA_R == 0b00001000) ){
            button_pressed = '3';
        }
        if((GPIO_PORTA_DATA_R == 0b000000100) && (GPIO_PORTE_DATA_R == 0b00000100) ){
            button_pressed = '6';
        }
        if((GPIO_PORTA_DATA_R == 0b000000100) && (GPIO_PORTE_DATA_R == 0b00000010) ){
            button_pressed = '9';
        }
        if((GPIO_PORTA_DATA_R == 0b000000100) && (GPIO_PORTE_DATA_R == 0b00000001) ){
            button_pressed = '#';
        }

        xQueueSend(scale_queue, &button_pressed, 5);
        vTaskDelay(5);
    }

}



