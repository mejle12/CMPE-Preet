/*
 * PWM_DRIVER.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Mike
 */

#include <stdint.h>
#include <stdio.h>
#include "LPC17xx.h"
#include "lpc_isr.h"
#include "gpio.hpp"
#include "PWM_DRIVER.h"
#include "FreeRTOSConfig.h"
#include "tasks.hpp"
#include "utilities.h"
#include "LABGPIOINTERRUPTS.hpp"
#include "io.hpp"
#include "FreeRTOS.h"
PWMDriver :: PWMDriver(){};
void PWMDriver :: pwmSelectAllPins(){
// Power Up the UART0
LPC_SC->PCONP |= (1 << 6);
// Selected Peripheral Clock to 12
LPC_SC-> PCLKSEL0 |= (6 << 12);
// Select All Pins
LPC_PINCON->PINSEL0 |= (1 << PWM_PIN_2_0);
LPC_PINCON->PINSEL1 |= (1 << PWM_PIN_2_1);
LPC_PINCON->PINSEL2 |= (1 << PWM_PIN_2_2);
LPC_PINCON->PINSEL3 |= (1 << PWM_PIN_2_3);
LPC_PINCON->PINSEL4 |= (1 << PWM_PIN_2_4);
LPC_PINCON->PINSEL7 |= (1 << PWM_PIN_2_5);
}
void PWMDriver :: pwmSelectPin(PWM_PIN pwm_pin_arg){
switch(pwm_pin_arg){
case PWM_PIN_2_0: {
LPC_PINCON->PINSEL0 |= (1 << PWM_PIN_2_0);
break;
}
case PWM_PIN_2_1: {
LPC_PINCON->PINSEL1 |= (1 << PWM_PIN_2_1);
break;
}
case PWM_PIN_2_2: {
LPC_PINCON->PINSEL2 |= (1 << PWM_PIN_2_2);
break;
}
case PWM_PIN_2_3: {
LPC_PINCON->PINSEL3 |= (1 << PWM_PIN_2_3);
break;
}
case PWM_PIN_2_4: {
LPC_PINCON->PINSEL4 |= (1 << PWM_PIN_2_4);
break;
}
case PWM_PIN_2_5: {
LPC_PINCON->PINSEL7 |= (1 << PWM_PIN_2_5);
break;
}
}
}
void PWMDriver :: pwmInitSingleEdgeMode(uint32_t frequency_Hz){
}
void PWMDriver :: setDutyCycle(PWM_PIN pwm_pin_arg, float duty_cycle_percentage){
}
void PWMDriver :: setFrequency(uint32_t frequency_Hz){
}
