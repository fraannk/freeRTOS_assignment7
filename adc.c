/*
 * adc.c
 *
 *  Created on: 25 Apr 2017
 *      Author: fraannk
 */
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"

void initADC(){

       SYSCTL_RCGC0_R |= 0x20000; // Enable ADC Clock
       GPIO_PORTB_AFSEL_R = 0x20;
       GPIO_PORTB_DEN_R = 0x00;
       GPIO_PORTB_AMSEL_R = 0xF; //disable analog isolation circuit
       ADC1_ACTSS_R = 0x00000000; //disable sampler sequence
       ADC1_EMUX_R = 0xF000;
       ADC1_SSMUX3_R = 0xB;
       ADC1_SSCTL3_R = 0x06;
       ADC1_IM_R = 0x08;
       ADC1_ACTSS_R = 0x00000008;


}

