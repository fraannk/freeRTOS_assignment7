/*
 * adc.h
 *
 *  Created on: 25 Apr 2017
 *      Author: fraannk
 */

#ifndef ADC_H_
#define ADC_H_

#include "FreeRTOS.h"
#include "queue.h"

extern xQueueHandle queue;

void initADC(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initiate ADC.
******************************************************************************/

void readADC(void *p);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Reading ADC.
******************************************************************************/

#endif /* ADC_H_ */
