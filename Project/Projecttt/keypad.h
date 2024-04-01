/*
 * keypad.h
 *
 *  Created on: Feb 15, 2024
 *      Author: PCM
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

#define Keypad_Rows 4
#define Keypad_Cols 4

#define Keypad_Rows_Port PORTB_ID
#define Keypad_Cols_Port PORTD_ID

#define Keypad_Rows_Pin PIN4_ID
#define Keypad_Cols_Pin PIN0_ID

#define Button_Press	LOGIC_LOW 	/*PULL UP*/
#define Button_Release	LOGIC_HIGH

uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
