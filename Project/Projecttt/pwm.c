/*
 * pwm.c
 *
 *  Created on: Feb 21, 2024
 *      Author: PCM
 */

#include "pwm.h"
#include "gpio.h"
#include "avr/io.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
	TCNT0 = 0;
	uint8 compare;
	compare=(duty_cycle*255)/100;
	OCR0  = compare;
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);

}

