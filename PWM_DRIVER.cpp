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

}

void PWMDriver :: pwmSelectPin(){

}

void PWMDriver :: pwnInitSingleEdgeMode(uint32_t frequency_Hz){

}

void PWMDriver :: setDutyCycle(){

}

void PWMDriver :: setFrequency(){

}
