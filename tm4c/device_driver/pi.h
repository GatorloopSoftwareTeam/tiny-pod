/*
 * pi.h
 *
 *  Created on: Aug 14, 2019
 *      Author: loki_
 */

#ifndef DEVICE_DRIVER_PI_H_
#define DEVICE_DRIVER_PI_H_

void piInit();
void piWaitForStart();
void piTransmitTemperature(int16_t temp);
void piTransmitVoltage(int16_t volts);
void piTransmitAcceleration(int16_t x, int16_t y, int16_t z);
void piTransmitGyroscope(int16_t x, int16_t y, int16_t z);

#endif /* DEVICE_DRIVER_PI_H_ */
