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
#include "gpio.h"
#include "lcd.h"
#include "numpad.h"

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
    initGPIO();
    initADC();
    initLCD();
    //initNumpad();

    // Warning: If you do not initialize the hardware clock, the timings will be inaccurate
    init_systick();
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
    xTaskCreate(readADC, (signed char*) "readADC", USERTASK_STACK_SIZE, NULL, HIGH_PRIO, NULL);
    xTaskCreate(readNumpad, (signed char*) "readNumpad", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
    //xTaskCreate(addNumbers, (signed char*) "addNumbers", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
    //xTaskCreate(makeUI, (signed char*) "makeUI", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);
    xTaskCreate(dispLCD, (signed char*) "dispLCD", USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL);

    // Start the scheduler.
    // --------------------
    vTaskStartScheduler();

    // Will only get here, if there was insufficient memory.
    // -----------------------------------------------------

  return 1;
}

/****************************** End Of Module *******************************/
