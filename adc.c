/*
 * adc.c
 *
 *  Created on: 25 Apr 2017
 *      Author: fraannk
 */
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"

void initADC(void) {
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

void readADC(void *p) {
    while(1){
        volatile static uint32_t result = 0; //ADC Result
        ADC1_PSSI_R = 0x0008; // initiate SS3 (sample sequencer 3)
        while((ADC1_RIS_R&0x08)==0){}; //wait for conversion done

        result = ADC1_SSFIFO3_R; //Read ADC and add it to result

        xQueueSend(adc_queue, &result, 5);

        if(result<1365){
            GPIO_PORTF_DATA_R = 0b0110;
        } else if(result>1366 && result<2729) {
            GPIO_PORTF_DATA_R = 0b1010;
        } else if(result>2730) {
            GPIO_PORTF_DATA_R = 0b1100;
        }
    }
}
