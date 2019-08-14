/*
 * l293d.c
 *
 *  Created on: Aug 14, 2019
 *      Author: loki_
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "driverlib/pwm.h"
#include "../board_driver/pwm_wrap.h"


void l293dInit()
{
    pwmInit();
}


void l293dSetSpeed(int16_t speed)
{
    speed = fmax(fmin(speed, 1000), -1000);
    if(speed < 0)
    {
        speed *= -1;
        pwmSetDuty(MOTOR_RIGHT_INVERT_BASE, MOTOR_RIGHT_INVERT, speed);
        pwmSetDuty(MOTOR_LEFT_INVERT_BASE, MOTOR_LEFT_INVERT, speed);
        pwmSetDuty(MOTOR_RIGHT_NORMAL_BASE, MOTOR_RIGHT_NORMAL, 0);
        pwmSetDuty(MOTOR_LEFT_NORMAL_BASE, MOTOR_LEFT_NORMAL, 0);
    }
    else
    {
        pwmSetDuty(MOTOR_RIGHT_INVERT_BASE, MOTOR_RIGHT_INVERT, 0);
        pwmSetDuty(MOTOR_LEFT_INVERT_BASE, MOTOR_LEFT_INVERT, 0);
        pwmSetDuty(MOTOR_RIGHT_NORMAL_BASE, MOTOR_RIGHT_NORMAL, speed);
        pwmSetDuty(MOTOR_LEFT_NORMAL_BASE, MOTOR_LEFT_NORMAL, speed);
    }
}
