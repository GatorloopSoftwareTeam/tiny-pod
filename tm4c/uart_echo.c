//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "bno055.h"
#include "pwm_wrap.h"
#include "delay.h"
#include "uart_wrap.h"

void waitForPiStart()
{

}

//Should be on timer interrupt
void sendPiImuData()
{
    //sends data over SPI


}

#define START_BYTE 0x17
#define STOP_BYTE 0x30

void transmitData(uint8_t reg, int16_t data)
{
    int8_t lowByte = data & 0xff;
    int8_t highByte = data >> 8;

    uartSendByte(START_BYTE);
    uartSendByte(reg);
    uartSendByte(lowByte);
    uartSendByte(highByte);
    uartSendByte(STOP_BYTE);
}


int main(void)
{
    /*
    bno055Init();
    InitPWM();

    //Waits for the start condition to be sent by the Raspberry PI
    waitForPiStart();

    //set max speed
    setSpeed(1000);

    //wait for 16 seconds
    delayMs(2000);

    //set 0
    setSpeed(0);
    */

    uartInit();

    while(1)
    {
       transmitData(0x1, 0x0300);
       delayMs(1000);
    }
}
