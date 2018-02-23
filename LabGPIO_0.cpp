/*
 * LabGPIO_0.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: Mike
 */
#include "LabGPIO_0.hpp"


LabGPIO_0::LabGPIO_0(uint8_t pin, uint8_t port){
mPinNum = pin;
mPortNum = port;

if (mPortNum == 0){
    LPC_GPIOx = LPC_GPIO0;
}else if (mPortNum == 1){
    LPC_GPIOx = LPC_GPIO1;
}else if (mPortNum == 2){
    LPC_GPIOx = LPC_GPIO2;
}
}

void LabGPIO_0::setAsInput(void){
    LPC_GPIOx->FIODIR &= ~(1 << mPinNum); // The Input Switch
     // The Reset Switch
}

void LabGPIO_0::setAsOutput(void){

    LPC_GPIOx->FIOPIN |= (1<< mPinNum); // The Output LED
}


void LabGPIO_0::setDirection(bool output){
    LPC_GPIOx -> FIODIR |= (1<< mPinNum);

}

void LabGPIO_0::setHigh(void){
    LPC_GPIOx->FIOSET = (1<< mPinNum);
}

void LabGPIO_0::setLow(void){
    LPC_GPIOx->FIOCLR = (1<< mPinNum);

}


void LabGPIO_0::set(bool high){
    (high) ? setHigh() : setLow();
}

bool LabGPIO_0::getLevel(void){

  return (LPC_GPIOx->FIOPIN & (1 << mPinNum));
}
