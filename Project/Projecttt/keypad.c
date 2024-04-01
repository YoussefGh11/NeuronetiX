/*
 * keypad.c
 *
 *  Created on: Feb 15, 2024
 *      Author: PCM
 */

#include "keypad.h"
#include "gpio.h"
#include <util/delay.h>


#if (Keypad_Cols == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (Keypad_Cols == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

uint8 KEYPAD_getPressedKey(void){

	uint8 row,col; /*3shan loop*/
	/* ROWS IP -- Configure 3shan lw kolo msh f nfs l port*/

	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+1,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+2,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+3,PIN_INPUT);

	/* Cols IP -- Configure 3shan lw kolo msh f nfs l port*/

	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin+1,PIN_INPUT);
	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin+2,PIN_INPUT);

	#if (Keypad_Cols == 4)
	GPIO_setupPinDirection(Keypad_Cols_Port,Keypad_Cols_Pin+3,PIN_INPUT); 	/*if 4x4*/
	#endif

	while(1){

		for (row=0;row<Keypad_Rows;row++){

			GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+row,PIN_OUTPUT);
			GPIO_writePin(Keypad_Rows_Port,Keypad_Rows_Pin+row,Button_Press);

				for(col=0;col<Keypad_Cols;col++){

					if( GPIO_readPin(Keypad_Cols_Port,Keypad_Cols_Pin+col) == Button_Press ){

						#if (Keypad_Cols == 3)
						return KEYPAD_4x3_adjustKeyNumber((row*Keypad_Cols)+col+1);
						#elif (Keypad_Cols == 4)
						return KEYPAD_4x4_adjustKeyNumber((row*Keypad_Cols)+col+1);
						#endif

						/*return (row*Keypad_Cols)+col+1;*/
					}

				}/*END col loop*/

			GPIO_setupPinDirection(Keypad_Rows_Port,Keypad_Rows_Pin+row,PIN_INPUT);
			_delay_ms(5); /* Add small delay to fix CPU load issue in proteus */

		}/*END row loop*/


	}/*END while*/


}/*END FN*/

#if (Keypad_Cols == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number){

	uint8 keypad_button = 0;

	switch(button_number)
	{
		case 10: keypad_button = '*';
				 break;
		case 11: keypad_button = 0;
				 break;
		case 12: keypad_button = '#';
				 break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#elif (Keypad_Cols == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number){

		uint8 keypad_button = 0;

		switch(button_number)
		{
			case 1: keypad_button = 7;
					break;
			case 2: keypad_button = 8;
					break;
			case 3: keypad_button = 9;
					break;
			case 4: keypad_button = '%'; // ASCII Code of %
					break;
			case 5: keypad_button = 4;
					break;
			case 6: keypad_button = 5;
					break;
			case 7: keypad_button = 6;
					break;
			case 8: keypad_button = '*'; /* ASCII Code of '*' */
					break;
			case 9: keypad_button = 1;
					break;
			case 10: keypad_button = 2;
					break;
			case 11: keypad_button = 3;
					break;
			case 12: keypad_button = '-'; /* ASCII Code of '-' */
					break;
			case 13: keypad_button = 13;  /* ASCII of Enter */ // ON
					break;
			case 14: keypad_button = 0;
					break;
			case 15: keypad_button = '='; /* ASCII Code of '=' */
					break;
			case 16: keypad_button = '+'; /* ASCII Code of '+' */
					break;
			default: keypad_button = button_number;
					break;
		}

	return keypad_button;
}
#endif
