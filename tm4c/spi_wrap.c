/*
 * spi_wrap.c
 *
 *  Created on: Aug 12, 2019
 *      Author: loki_
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

void spiInit()
{
    //Enable SSI0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    //Enabe Peripheral on GPIOA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //Configure the pin muxing for SSI0 functions
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    //Enable SSI pins
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);

    //Configure SSI
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 10000, 16);

    //enable SSI
    SSIEnable(SSI0_BASE);
}

void spiSend(uint32_t data)
{
    SSIDataPut(SSI0_BASE, data);
    while(SSIBusy(SSI0_BASE));
}


