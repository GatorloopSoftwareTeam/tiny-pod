#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>


#ifndef PWM_WRAP_H_
#define PWM_WRAP_H_


#define MOTOR_LEFT_NORMAL_BASE PWM1_BASE //PF2
#define MOTOR_LEFT_INVERT_BASE PWM1_BASE //PF3
#define MOTOR_RIGHT_NORMAL_BASE PWM0_BASE //PB7
#define MOTOR_RIGHT_INVERT_BASE PWM0_BASE //PB6

#define MOTOR_LEFT_NORMAL PWM_OUT_6 //PF2
#define MOTOR_LEFT_INVERT PWM_OUT_7 //PF3
#define MOTOR_RIGHT_NORMAL PWM_OUT_1 //PB7
#define MOTOR_RIGHT_INVERT PWM_OUT_0 //PB6

extern void InitPWM(void);
extern void setSpeed(int16_t speed);

#endif /* PWM_WRAP_H_ */
