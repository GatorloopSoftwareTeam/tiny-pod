/*
 * pi.c
 *
 *  Created on: Aug 14, 2019
 *      Author: loki_
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "../board_driver/uart_wrap.h"

/*
 * Private Constants
 */

#define START_BYTE 0x17
#define STOP_BYTE 0x30
#define ESCAPE_BYTE 0x7D

#define TEMP_ADDR 0x01
#define ACCEL_ADDR 0x02
#define GYRO_ADDR 0x03
#define VOLT_ADDR 0x04


void sendPacket(int8_t data[], int length);
void transmitData(uint8_t reg, int16_t packetData[], int dataLength);
void transmitXYZ(uint8_t reg, int16_t x, int16_t y, int16_t z);
void transmitValue(uint8_t reg, int16_t value);


/*
 * Public functions
 */

void piInit()
{
    uartInit();
}

void piWaitForStart()
{

}

void piTransmitTemperature(int16_t temp)
{
    transmitValue(TEMP_ADDR, temp);
}

void piTransmitVoltage(int16_t volts)
{
    transmitValue(VOLT_ADDR, volts);
}


void piTransmitAcceleration(int16_t x, int16_t y, int16_t z)
{
    transmitXYZ(ACCEL_ADDR, x, y, z);
}

void piTransmitGyroscope(int16_t x, int16_t y, int16_t z)
{
    transmitXYZ(GYRO_ADDR, x, y, z);
}


/*
 * Private functions
 */

void transmitXYZ(uint8_t reg, int16_t x, int16_t y, int16_t z)
{
    int16_t packet[3] = {x, y, z};
    transmitData(reg, packet, 3);
}

void transmitValue(uint8_t reg, int16_t value)
{
    int16_t packet[1] = { value };
    transmitData(reg, packet, 1);
}

void transmitData(uint8_t reg, int16_t packetData[], int dataLength)
{
    int8_t packet[50];
    packet[0] = reg;
    int packetLength = 1;

    int index;
    for (index = 0; index < dataLength; index++)
    {
        int16_t data = packetData[index];
        int8_t lowByte = data & 0xff;
        int8_t highByte = data >> 8;
        packet[packetLength] = lowByte;
        packetLength++;
        packet[packetLength] = highByte;
        packetLength++;
    }

    sendPacket(packet, packetLength);
}

void sendPacket(int8_t data[], int length)
{
    uartSendByte(START_BYTE);
    int index;
    for(index = 0; index < length; index++)
    {
        uint8_t byte = data[index];

        if (byte == START_BYTE || byte == STOP_BYTE || byte == ESCAPE_BYTE)
            uartSendByte(ESCAPE_BYTE);

        uartSendByte(byte);
    }

    uartSendByte(STOP_BYTE);
}
