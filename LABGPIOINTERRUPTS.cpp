/*
 * LABGPIOINTERRUPTS.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Mike
 */
#include <stdint.h>
#include <stdio.h>
#include "LPC17xx.h"
#include "lpc_isr.h"
#include "gpio.hpp"
#include "FreeRTOSConfig.h"
#include "tasks.hpp"
#include "utilities.h"
#include "LABGPIOINTERRUPTS.hpp"
#include "io.hpp"
#include "FreeRTOS.h"

LabGPIOInterrupts * LabGPIOInterrupts :: ptrInstance = NULL ;
LabGPIOInterrupts * LabGPIOInterrupts :: Instance ()
{
if ( ptrInstance == NULL )
{
ptrInstance = new LabGPIOInterrupts ();
}
return ptrInstance ;
}
LabGPIOInterrupts :: LabGPIOInterrupts (){};
void LabGPIOInterrupts :: init ()
{
isr_register ( EINT3_IRQn , externalIRQHandler );
NVIC_EnableIRQ ( EINT3_IRQn );
}
bool LabGPIOInterrupts :: attachInterruptHandler ( uint8_t port , uint32_t pin , void
(* pin_isr )( void ), uint8_t condition )
{
PortNum = port ;
PinNum = pin ;
bool tst ;
if ( PortNum == 0 )
{
tst = false ;
if ( condition )
{
if ( condition == 0 )
{
LPC_GPIOINT -> IO0IntEnF |=( 1 << PinNum );
}
else if ( condition == 1 )
{
LPC_GPIOINT -> IO0IntEnR |=( 1 << PinNum );
}
else
{
LPC_GPIOINT -> IO0IntEnR |=( 1 << PinNum );
LPC_GPIOINT -> IO0IntEnF |=( 1 << PinNum );
}
}
}
else if ( PortNum == 2 )
{
tst = true ;
if ( condition )
{
if ( condition == 0 )
{
LPC_GPIOINT -> IO2IntEnF |=( 1 << PinNum );
}
else if ( condition == 1 )
{
LPC_GPIOINT -> IO2IntEnR |=( 1 << PinNum );
}
else
{
LPC_GPIOINT -> IO2IntEnR |=( 1 << PinNum );
LPC_GPIOINT -> IO2IntEnF |=( 1 << PinNum );
}
}
}
return tst ;
}
void LabGPIOInterrupts :: externalIRQHandler (){
if ( LPC_GPIOINT -> IO0IntStatR & ( 1 << 1 ) || LPC_GPIOINT -> IO0IntStatF & ( 1 << 1 ))
{
LPC_GPIOINT -> IO0IntClr = ( 1 << 1 );
printf ( "P0.1 Interrupt!\n" ); // test

}
if ( LPC_GPIOINT -> IO2IntStatR & ( 1 << 8 ) || LPC_GPIOINT -> IO2IntStatF & ( 1 << 7 ))
{
LPC_GPIOINT -> IO2IntClr = ( 1 << 8 );
printf ( "P2.8 Interrupt!\n" ); // test


}

}


