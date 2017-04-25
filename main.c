/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 2, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick_frt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"

/*****************************    Defines    *******************************/
#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO 0
#define LOW_PRIO  1
#define MED_PRIO  2
#define HIGH_PRIO 3


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/


int putChar()
/*****************************************************************************
*   Input    :  -
*   Output   :  Result
*   Function :  putChar for FreeRTOS debug functionality.
*****************************************************************************/
{
  return(0);
}

static void setupHardware(void)
/*****************************************************************************
*   Input    :  -
*   Output   :  -
*   Function :
*****************************************************************************/
{
  // TODO: Put hardware configuration and initialisation in here

  // Warning: If you do not initialize the hardware clock, the timings will be inaccurate
  //init_systick();
}



int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
    setupHardware();

    // Start the tasks.
    // ----------------

    // Start the scheduler.
    // --------------------
    //vTaskStartScheduler();

    // Will only get here, if there was insufficient memory.
    // -----------------------------------------------------

    SYSCTL_RCGC2_R = 0b00100010;
    int dummy = SYSCTL_RCGC2_R;
    GPIO_PORTF_DIR_R = 0xE; //Set gr�n, gul og r�d LED pins til output
    GPIO_PORTF_DEN_R = 0xE; // enable digital pins
    GPIO_PORTF_DATA_R = 0b0000;

    initADC();

    while(1){
    volatile static uint32_t Result = 0; //ADC Result
    ADC1_PSSI_R = 0x0008; // initiate SS3 (sample sequencer 3)
    while((ADC1_RIS_R&0x08)==0){}; //wait for conversion done

    Result = ADC1_SSFIFO3_R; //Read ADC and add it to Result
    if(Result<1365){
    GPIO_PORTF_DATA_R = 0b0110;

    }

    if(Result>1366&&Result<2729) {
    GPIO_PORTF_DATA_R = 0b1010;

    }

    if(Result>4000) {
    GPIO_PORTF_DATA_R = 0b1100;

    }
    }
  return 1;
}

/****************************** End Of Module *******************************/
