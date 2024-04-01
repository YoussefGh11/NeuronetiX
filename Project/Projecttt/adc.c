/*
 * adc.c
 *
 *  Created on: Feb 20, 2024
 *      Author: PCM
 */


#include "common_macros.h"
#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16 g_adcResult = 0;

ISR (ADC_vect){

	g_adcResult=ADC; //ADC value
}

void ADC_init(const ADC_ConfigType * Config_Ptr){

	SET_BIT(SREG,7); // IBit
	ADMUX&=0XE0; //To reset Channels
	ADMUX = (ADMUX & 0x3F) | (Config_Ptr->ref_volt); /*dynamic config for REFERENCE*/
	SET_BIT(ADCSRA,ADEN); //ADC ENABLE
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler); /*dynamic config for divison factor*/
	SET_BIT(ADCSRA,ADIE); //INT ENABLE
}

void ADC_readChannel(uint8 channel_number){

	channel_number &= 0x07; //for safety en channel num mn 0 l 7
	ADMUX&=0XE0; //clearr
	ADMUX = ADMUX | channel_number; //insert
	SET_BIT(ADCSRA,ADSC); //START CONV

}
