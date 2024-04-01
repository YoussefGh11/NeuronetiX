/*
 * lcd.h
 *
 *  Created on: Feb 16, 2024
 *      Author: PCM
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

#define Data_Mode 8

#define RS_PORT PORTB_ID
#define RS_PIN	PIN0_ID

#define E_PORT	PORTB_ID
#define E_PIN	PIN1_ID

#if (Data_Mode == 8)
#define DP_PORT PORTC_ID
#define Function_Set 0x38
#elif (Data_Mode == 4)
#define DP_PORT PORTA_ID
#define DP_FIRST_PIN PIN3_ID
#define Function_Set 0x28
#define Function_Set1 0x33
#define Function_Set2 0x32
#endif

#define Cursor_OFF 0x0C
#define Cursor_ON 0x0E

#define LCD_Clear 0x01

void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_clearScreen(void);
void LCD_intgerToString(int data);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

#endif /* LCD_H_ */
