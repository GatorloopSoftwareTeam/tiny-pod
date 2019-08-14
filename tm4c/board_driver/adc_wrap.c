/*
 * adc.c
 *
 *  Created on: Aug 7, 2019
 *      Author: loki_
 */

/*
void initAdc()
{
    //
    // Enable the clock to the ADC module
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    //
    // Configure the ADC to sample at 500KSps
    //
    //SysCtlADCSpeedSet(SYSCTL_SET0_ADCSPEED_500KSPS);

    //
    // Disable sample sequences 1 and 3
    //
    ADCSequenceDisable(ADC0_BASE, 1);
    ADCSequenceDisable(ADC0_BASE, 3);

    //
    // Configure sample sequence 1: timer trigger, priority = 1
    //
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_TIMER, 1);

    //
    // Configure sample sequence 3: processor trigger, priority = 0
    //
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    //
    // Configure sample sequence 3 steps 0, 1 and 2
    //
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);

    //
    // Configure sample sequence 3 step 0
    //
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_TS | ADC_CTL_END);
}


void getADC()
{
    //
    // Retrieve data from sample sequence 1 FIFO
    //
    ADCSequenceDataGet(ADC0_BASE, 1, &ulSeq1DataBuffer);
    //
    // Retrieve data from sample sequence 3 FIFO
    //
    ADCSequenceDataGet(ADC0_BASE, 3, &ulSeq3DataBuffer);
}
*/
