
/*
 *  ======== pwmtest.c ========
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/I2C.h>


#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"


/* Example/Board Header files */
#include "Board.h"
/* Board: EK_TM4C123GXL_ */

#define BNO055_ADDRESS 0x28

typedef enum BNO055_ADDRESSES
{
    CHIP_ID = 0,
    ACC_ID,
    MAG_ID,
    GYR_ID,
    SW_REV_ID_LSB,
    SW_REV_ID_MSB,
    BL_REV_ID,
    PAGE_ID,
    ACC_DATA_X_LSB,
    ACC_DATA_X_MSB,
    ACC_DATA_Y_LSB,
    ACC_DATA_Y_MSB,
    ACC_DATA_Z_LSB,
    ACC_DATA_Z_MSB,
    MAG_DATA_X_LSB,
    MAG_DATA_X_MSB,
    MAG_DATA_Y_LSB,
    MAG_DATA_Y_MSB,
    MAG_DATA_Z_LSB,
    MAG_DATA_Z_MSB,
    GYR_DATA_X_LSB,
    GYR_DATA_X_MSB,
    GYR_DATA_Y_LSB,
    GYR_DATA_Y_MSB,
    GYR_DATA_Z_LSB,
    GYR_DATA_Z_MSB,
    EUL_DATA_X_LSB,
    EUL_DATA_X_MSB,
    EUL_DATA_Y_LSB,
    EUL_DATA_Y_MSB,
    EUL_DATA_Z_LSB,
    EUL_DATA_Z_MSB,
    QUA_DATA_W_LSB,
    QUA_DATA_W_MSB,
    QUA_DATA_X_LSB,
    QUA_DATA_X_MSB,
    QUA_DATA_Y_LSB,
    QUA_DATA_Y_MSB,
    QUA_DATA_Z_LSB,
    QUA_DATA_Z_MSB,
    LIA_DATA_X_LSB,
    LIA_DATA_X_MSB,
    LIA_DATA_Y_LSB,
    LIA_DATA_Y_MSB,
    LIA_DATA_Z_LSB,
    LIA_DATA_Z_MSB,
    GRV_DATA_X_LSB,
    GRV_DATA_X_MSB,
    GRV_DATA_Y_LSB,
    GRV_DATA_Y_MSB,
    GRV_DATA_Z_LSB,
    GRV_DATA_Z_MSB,
    TEMP,
    CALIB_STAT,
    ST_RESULT,
    INT_STA,
    SYS_CLK_STATUS,
    SYS_STATUS,
    SYS_ERR,
    UNIT_SEL,
    OPR_MODE = 0x3D,
    PWR_MODE,
    SYS_TRIGGER,
    TEMP_SOURCE,
    AXIS_MAP_CONFIG,
    AXIS_MAP_SIGN,
    ACC_OFFSET_X_LSB = 0x55,
    ACC_OFFSET_X_MSB,
    ACC_OFFSET_Y_LSB,
    ACC_OFFSET_Y_MSB,
    ACC_OFFSET_Z_LSB,
    ACC_OFFSET_Z_MSB,
    MAG_OFFSET_X_LSB,
    MAG_OFFSET_X_MSB,
    MAG_OFFSET_Y_LSB,
    MAG_OFFSET_Y_MSB,
    MAG_OFFSET_Z_LSB,
    MAG_OFFSET_Z_MSB,
    GYR_OFFSET_X_LSB,
    GYR_OFFSET_X_MSB,
    GYR_OFFSET_Y_LSB,
    GYR_OFFSET_Y_MSB,
    GYR_OFFSET_Z_LSB,
    GYR_OFFSET_Z_MSB,
    ACC_RADIUS_LSB,
    ACC_RADIUS_MSB,
    MAG_RADIUS_LSB,
    MAG_RADIUS_MSB
} BNO055_ADDRESSES;


//initialize I2C module 0
//Slightly modified version of TI's example code
void InitI2C0(void)
{
    //System_printf("Initializing I2C...\n");
    //System_flush();
    //enable I2C module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    //reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    //enable GPIO peripheral that contains I2C 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    //clear I2C FIFOs
    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
    //System_printf("I2C Initialized.\n");
    //System_flush();
}

//sends an I2C command to the specified slave
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //stores list of variable number of arguments
    va_list vargs;

    //specifies the va_list to "open" and the last fixed argument
    //so vargs knows where to start looking
    va_start(vargs, num_of_args);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(num_of_args == 1)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable argument list
        va_end(vargs);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        uint8_t i;
        for(i = 1; i < (num_of_args - 1); i++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
            //send next data that was just placed into FIFO
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C0_BASE));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C0_BASE, va_arg(vargs, uint32_t));
        //send next data that was just placed into FIFO
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable args list
        va_end(vargs);
    }
}

//read specified register on slave device
uint8_t I2CReceive(uint32_t slave_addr, uint8_t reg)
{
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C0_BASE, reg);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //return data pulled from the specified register
    return I2CMasterDataGet(I2C0_BASE);
}

struct bn055_accel
{
    int16_t x;
    int16_t y;
    int16_t z;
};

uint8_t bn055ReadReg(uint8_t reg)
{
    return (uint8_t)I2CReceive(BNO055_ADDRESS, reg);
}

void bn055SendReg(uint8_t reg, uint8_t data)
{
    I2CSend(BNO055_ADDRESS, 2, reg, data);
}

int16_t bn055ReadData(uint8_t lsbReg)
{
    uint8_t msbReg = lsbReg + 1; //Little endian

    uint8_t lsbData = bn055ReadReg(lsbReg);
    uint8_t msbData = bn055ReadReg(msbReg);


    return (msbData << 8) | lsbData;
}

struct bn055_accel bn055ReadAccel()
{
    struct bn055_accel data;

    data.x = bn055ReadData(ACC_DATA_X_LSB);
    data.y = bn055ReadData(ACC_DATA_Y_LSB);
    data.z = bn055ReadData(ACC_DATA_Z_LSB);
    return data;
}

void bn055Init()
{
    InitI2C0();
    bn055SendReg(OPR_MODE, 0x01);
}


int main(void)
{
    bn055Init();
    //ConfigureUART();
    //UARTprintf("Hello, world!\n");
    while(1)
    {
        struct bn055_accel accel = bn055ReadAccel();
        //UARTprintf("%d", accel.z);
        System_printf("\nAcceleration:\n");
        System_printf("x:%d\n",accel.x);
        System_printf("y:%d\n",accel.y);
        System_printf("z:%d\n",accel.z);
        System_flush();
    }

    return 0;
}

