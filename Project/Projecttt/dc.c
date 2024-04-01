/*
 * dc.c
 *
 *  Created on: Feb 21, 2024
 *      Author: PCM
 */


#include 	"gpio.h"
#include 	"common_macros.h"
#include 	"dc.h"
#include 	"pwm.h"

void DcMotor_Init(void){

	/* direction of IN1/IN2 of motor as OP/s*/

	GPIO_setupPinDirection(PORTA_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN2_ID,PIN_OUTPUT);

	/* turn off dc motor at beginning */
	GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
	GPIO_writePin(PORTA_ID,PIN2_ID,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){


	switch(state){

	case Stop:
		PWM_Timer0_Start(speed);
		GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
		GPIO_writePin(PORTA_ID,PIN2_ID,LOGIC_LOW);
		break;
	case CW:
		PWM_Timer0_Start(speed);
		GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
		GPIO_writePin(PORTA_ID,PIN2_ID,LOGIC_HIGH);
		break;
	case ACW:
		PWM_Timer0_Start(speed);
		GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_HIGH);
		GPIO_writePin(PORTA_ID,PIN2_ID,LOGIC_LOW);
		break;
	}

}
