#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "bno055.h"
#include "../board_driver/i2c_wrap.h"

void bno055Init()
{
    I2C0Init();
    //configure sensors
    bno055SendReg(OPR_MODE, IMU);
}

uint8_t bno055ReadReg(uint8_t reg)
{
    return (uint8_t)I2CReceive(BNO055_ADDRESS, reg);
}

void bno055SendReg(uint8_t reg, uint8_t data)
{
    I2CSend(BNO055_ADDRESS, 2, reg, data);
}

int16_t bno055ReadData(uint8_t lsbReg)
{
    uint8_t msbReg = lsbReg + 1; //Little endian

    uint8_t lsbData = bno055ReadReg(lsbReg);
    uint8_t msbData = bno055ReadReg(msbReg);


    return (msbData << 8) | lsbData;
}

struct bno055_3axis bno055Read3Axis(uint8_t reg)
{
    struct bno055_3axis data;
    data.x = bno055ReadData(reg);
    data.y = bno055ReadData(reg+2);
    data.z = bno055ReadData(reg+4);
    return data;
}

struct bno055_3axis bno055ReadAccel()
{
    return bno055Read3Axis(ACC_DATA_X_LSB);
}
struct bno055_3axis bno055ReadGyro()
{
    return bno055Read3Axis(GYR_DATA_X_LSB);
}
struct bno055_3axis bno055ReadMag()
{
    return bno055Read3Axis(MAG_DATA_X_LSB);
}
struct bno055_3axis bno055ReadHead()
{
    return bno055Read3Axis(EUL_DATA_X_LSB);
}
struct bno055_quat bno055ReadQuat()
{
    struct bno055_quat quat;
    quat.w = bno055ReadData(QUA_DATA_W_LSB);
    quat.x = bno055ReadData(QUA_DATA_X_LSB);
    quat.y = bno055ReadData(QUA_DATA_Y_LSB);
    quat.z = bno055ReadData(QUA_DATA_Z_LSB);
    return quat;
}
struct bno055_3axis bno055ReadLinAccel()
{
    return bno055Read3Axis(LIA_DATA_X_LSB);
}
struct bno055_3axis bno055ReadGrav()
{
    return bno055Read3Axis(GRV_DATA_X_LSB);
}
uint8_t bno055ReadTemp()
{
    return bno055ReadReg(TEMP);
}
