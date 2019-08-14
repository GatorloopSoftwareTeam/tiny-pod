#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"

#include "pwm_wrap.h"


void pwmInit(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enables the peripherals on port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //enables the peripherals on port B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); //enable PWM 0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); //enable PWM 1 peripheral

    SysCtlPWMClockSet(SYSCTL_PWMDIV_1); //set clock divide for generators to 1

    /*
     * allows the lock placed on the pins of the GPIO module to be removed so that
       additional functionality may be used, in this case PWM. Without this, the pin will not be
       available for use by any other module besides the module it is linked with.
     */

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTB_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTB_BASE + GPIO_O_CR) |= 0x01;


    /*
     *  configures to use a specific pin on the PWM module.
     */
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    GPIOPinConfigure(GPIO_PB6_M0PWM0);

    /*
     * sets the functionality of the GPIO pin within the GPIO module.
     */
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

    /*
     *  configures the PWM generator on the module. The generator creates the pulses
        needed for PWM output.
     */
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    /*
        Sets the period of the PWM output..
     */
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 1000);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 1000);

    /*
        sets the pulse width, or duty cycle of the output to the PWM pins.
    */

    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 0); //PF2
    PWMOutputInvert(PWM1_BASE, PWM_OUT_6_BIT, true);

    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 0); //PF3
    PWMOutputInvert(PWM1_BASE, PWM_OUT_7_BIT, true);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 0); //PB7
    PWMOutputInvert(PWM0_BASE, PWM_OUT_1_BIT, true);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 0); //PB6
    PWMOutputInvert(PWM0_BASE, PWM_OUT_0_BIT, true);

    /*
     * enables the PWM generator. Now that the previous values have been set, the
        generator may now be turned on.
     */
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    /*
     * enables the PWM module to start modify the pins set for PWM output
     */
    PWMOutputState(PWM0_BASE, (PWM_OUT_0_BIT | PWM_OUT_1_BIT), true);
    PWMOutputState(PWM1_BASE, (PWM_OUT_6_BIT | PWM_OUT_7_BIT), true);
}

void PWMSetDuty(uint32_t base, uint32_t pwm_out, int16_t duty)
{
    int outbit;

    if (pwm_out == PWM_OUT_0)
            outbit = PWM_OUT_0_BIT;
    else if (pwm_out == PWM_OUT_1)
            outbit = PWM_OUT_1_BIT;
    else if (pwm_out == PWM_OUT_2)
            outbit = PWM_OUT_2_BIT;
    else if (pwm_out == PWM_OUT_3)
            outbit = PWM_OUT_3_BIT;
    else if (pwm_out == PWM_OUT_4)
        outbit = PWM_OUT_4_BIT;
    else if (pwm_out == PWM_OUT_5)
        outbit = PWM_OUT_5_BIT;
    else if (pwm_out == PWM_OUT_6)
        outbit = PWM_OUT_6_BIT;
    else if (pwm_out == PWM_OUT_7)
        outbit = PWM_OUT_7_BIT;


    PWMOutputInvert(base, outbit, duty == 0);

    PWMPulseWidthSet(base, pwm_out, duty);
}
