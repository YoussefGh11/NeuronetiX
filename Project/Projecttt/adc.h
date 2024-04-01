/*
 * adc.h
 *
 *  Created on: Feb 20, 2024
 *      Author: PCM
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   5
extern volatile uint16 g_adcResult;

typedef enum {AREF,AVCC,RESERVED,INTERNAL}ADC_ReferenceVolatge;
typedef enum {DivisonFactor,DivisonFactor2,DivisonFactor4,DivisonFactor8,DivisonFactor16,DivisonFactor32,DivisonFactor64,DivisonFactor128}
ADC_Prescaler;

typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;

void ADC_init(const ADC_ConfigType * Config_Ptr);
void ADC_readChannel(uint8 channel_number);

#endif /* ADC_H_ */
