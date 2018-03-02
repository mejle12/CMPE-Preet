#include "FreeRTOS.h"
#include "task.h"
#include "uart0_min.h"
#include "LABGPIOINTERRUPTS.hpp"
#include "LABGPIO_0.hpp"
#include "gpio.hpp"
#include "io.hpp"
#include "tasks.hpp"
#include "FreeRTOSConfig.h"
#include "utilities.h"

#include <stdio.h>
/*
void vTaskOneCode(void *)

{
    while(1)
    {
    	uart0_puts("aaaaaaaaaaaaaaaaaaaa");
    	vTaskDelay(100); // This sleeps the task for 100ms (because 1 RTOS tick = 1 millisecond)
    }
}

// Create another task and run this code in a while(1) loop
void vTaskTwoCode(void *)
{
    while(1)
    {
    	uart0_puts("bbbbbbbbbbbbbbbbbbbb");
    	vTaskDelay(100);
    }
}
*/

/* LOOK UP TABLE
const uint32_t PortNum[2]{
    [0] = 0, [1]=1, [2]=2
};

const uint32_t PinNum [32]{
    [0] = 0,
    [1] = 1,
    [2] = 2,
    [3] = 3,
    [4] = 4,
    [5] = 5,
    [6] = 6,
    [7] = 7,
    [8] = 8,
    [9] = 9,
    [10] = 10,
    [11] = 11,
    [12] = 12,
    [13] = 13,
    [14] = 14,
    [15] = 15,
    [16] = 16,
    [17] = 17,
    [18] = 18,
    [19] = 19,
    [20] = 20,
    [21] = 21,
    [22] = 22,
    [23] = 23,
    [24] = 24,
    [25] = 25,
    [26] = 26,
    [27] = 27,
    [28] = 28,
    [29] = 29,
    [30] = 30,
    [31] = 31,
    [32] = 32
};

*/
SemaphoreHandle_t xSemaphore ;
void SWITCH ( void )
{
if ( LPC_GPIOINT -> IO0IntStatR & ( 1 << 1 ) || LPC_GPIOINT -> IO0IntStatF & ( 1 << 1 ))
{
LPC_GPIOINT -> IO0IntClr = ( 1 << 1 );
printf ( "P0.1 Interrupt!\n" ); // test interrupt
xSemaphoreGive ( xSemaphore ); //
}
}
void SWITCH2 ( void )
{
if ( LPC_GPIOINT -> IO2IntStatR & ( 1 << 8 ) || LPC_GPIOINT -> IO2IntStatF & ( 1 << 8 )) // Look at PDF to check Pin Numbers
{
LPC_GPIOINT -> IO2IntClr = ( 1 << 8 );
printf ( "P2.7 Interrupt!\n" ); // PrintF to test interrupt
xSemaphoreGive ( xSemaphore );
}
}
void vControlLED ( void *) // updated LED control
{
LabGPIO_0 lit ( 0 , 0 );
lit . setAsOutput ();
int temp = 0 ;
while ( 1 )
{
if ( xSemaphoreTake ( xSemaphore , portMAX_DELAY ))
{
temp ++;
if ( temp % 2 == 0 )
{
if ( lit . getLevel () == 1 )
{
lit . setLow ();
}
else
{
lit . setHigh ();
}
}
}
}
}


void vOLDControlLED( void * pvParameters )
{

    /* Get Parameter */
    uint32_t param = (uint32_t)(pvParameters);
    /* Define Constants Here */

    /* Define Local Variables and Objects */

    /* Initialization Code */

    while(1)
    {
        /* Insert Loop Code */
    }
    /* Only necessary if above loop has a condition */
 //   xTaskDelete(NULL);
}

// Control LED Internal
void vReadSwitch (void *)
{
    LabGPIO_0 LED (4,1);
    LabGPIO_0 SWTCH (9,1);

    SWTCH.setAsInput();
    LED.setAsOutput();
while (1){
  if (SWTCH.getLevel() == true){ // Switch is toggled LED comes up
      LED.setLow();
    }else{
        LED.setHigh();
    }

    // TEST CODE IS BELOW

   /* LED.setHigh();
    vTaskDelay(1000);
    LED.setLow();
    vTaskDelay(1000);
    */
}
//    xTaskDelete(NULL);
}

// Control LED External

void vExtraCredit (void *){

}

int main(int argc, char const *argv[])

{
const uint32_t STACK_SIZE = 1024;
LabGPIOInterrupts :: Instance ()-> attachInterruptHandler ( 0 , 1 , SWITCH , 1 ); // Switch Test
LabGPIOInterrupts :: Instance ()-> init ();


// Some other Shit...

xSemaphore = xSemaphoreCreateBinary (); // Semaphore. Great...

isr_register ( EINT3_IRQn , SWITCH ); // Register


//// ALL CREATED TASKS GO BELOW
xTaskCreate ( vControlLED , "LIT" , 1024 , ( void * ) 0 , PRIORITY_LOW , NULL );
/*

    xTaskCreate(vTaskTwoCode, "t2", 1024, NULL, 1, NULL);
*/

// xTaskCreate(vReadSwitchEXT, "rse", 1024, NULL, 1, NULL);
// xTaskCreate(vReadSwitchINT, "rsi", 1024, NULL, 1, NULL);
//xTaskCreate(vReadSwitch, "vrs", 1024, NULL, 1, NULL);
// xTaskCreate(vControlLEDEXT, "cle", 1024, NULL, 1, NULL);


    /* Start Scheduler - This will not return, and your tasks will start to run their while(1) loop */
    vTaskStartScheduler();

    return 0;
}
