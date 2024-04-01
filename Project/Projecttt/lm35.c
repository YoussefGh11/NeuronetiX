/*
 * lm35.c
 *
 *  Created on: Feb 20, 2024
 *      Author: PCM
 */


#include "lm35.h"
#include "adc.h"
#include <util/delay.h>

uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

	ADC_readChannel(SENSOR_CHANNEL_ID);
	_delay_ms(5);

	temp_value = (uint8)(((uint32)g_adcResult*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}
