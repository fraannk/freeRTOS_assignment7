/*
 * gpio.c
 *
 *  Created on: 25 Apr 2017
 *      Author: fraannk
 */
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"

void initGPIO(void) {
    //Init GPIO:
    SYSCTL_RCGC2_R = 0b00100010;
    int dummy = SYSCTL_RCGC2_R;
    GPIO_PORTF_DIR_R = 0xE; //Set gr�n, gul og r�d LED pins til output
    GPIO_PORTF_DEN_R = 0xE; // enable digital pins
    GPIO_PORTF_DATA_R = 0b0000;
}
