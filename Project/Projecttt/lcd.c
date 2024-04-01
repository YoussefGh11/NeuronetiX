/*
 * lcd.c
 *
 *  Created on: Feb 16, 2024
 *      Author: PCM
 */


#include	"lcd.h"
#include 	"gpio.h"
#include 	"common_macros.h"
#include 	<util/delay.h>

void LCD_init(void){

	GPIO_setupPinDirection(RS_PORT,RS_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(E_PORT,E_PIN,PIN_OUTPUT);

	#if (Data_Mode == 8)
	GPIO_setupPortDirection(DP_PORT,PORT_OUTPUT);
	#elif (Data_Mode == 4)
	GPIO_setupPinDirection(DP_PORT,DP_FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DP_PORT,DP_FIRST_PIN+1,PIN_OUTPUT);
	GPIO_setupPinDirection(DP_PORT,DP_FIRST_PIN+2,PIN_OUTPUT);
	GPIO_setupPinDirection(DP_PORT,DP_FIRST_PIN+3,PIN_OUTPUT);
	#endif

	_delay_ms(20);

	#if (Data_Mode == 8)
	LCD_sendCommand(Function_Set);
	#elif (Data_Mode == 4)
	LCD_sendCommand(Function_Set);
	LCD_sendCommand(Function_Set1);
	LCD_sendCommand(Function_Set2);
	#endif
	LCD_sendCommand(Cursor_OFF);
	LCD_sendCommand(LCD_Clear);

}

void LCD_sendCommand(uint8 command){

	GPIO_writePin(RS_PORT,RS_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);
#if (Data_Mode == 8)
	GPIO_writePort(DP_PORT,command);
	_delay_ms(1);
#elif (Data_Mode == 4)
		GPIO_writePin(DP_PORT,DP_FIRST_PIN,GET_BIT(command,4));
		GPIO_writePin(DP_PORT,DP_FIRST_PIN+1,GET_BIT(command,5));
		GPIO_writePin(DP_PORT,DP_FIRST_PIN+2,GET_BIT(command,6));
		GPIO_writePin(DP_PORT,DP_FIRST_PIN+3,GET_BIT(command,7));

		_delay_ms(1);
		GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
		_delay_ms(1);
		GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
		_delay_ms(1);

		GPIO_writePin(DP_PORT,DP_FIRST_PIN,GET_BIT(command,0));
		GPIO_writePin(DP_PORT,DP_FIRST_PIN+1,GET_BIT(command,1));
		GPIO_writePin(DP_PORT,DP_FIRST_PIN+2,GET_BIT(command,2));
		GPIO_writePin(DP_PORT,DP_FIRST_PIN+3,GET_BIT(command,3));
		_delay_ms(1);
#endif
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
}

void LCD_displayCharacter(uint8 data){

	GPIO_writePin(RS_PORT,RS_PIN,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);
#if (Data_Mode == 8)
	GPIO_writePort(DP_PORT,data);
	_delay_ms(1);
#elif (Data_Mode == 4)
			GPIO_writePin(DP_PORT,DP_FIRST_PIN,GET_BIT(data,4));
			GPIO_writePin(DP_PORT,DP_FIRST_PIN+1,GET_BIT(data,5));
			GPIO_writePin(DP_PORT,DP_FIRST_PIN+2,GET_BIT(data,6));
			GPIO_writePin(DP_PORT,DP_FIRST_PIN+3,GET_BIT(data,7));

			_delay_ms(1);
			GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
			_delay_ms(1);
			GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
			_delay_ms(1);

			GPIO_writePin(DP_PORT,DP_FIRST_PIN,GET_BIT(data,0));
			GPIO_writePin(DP_PORT,DP_FIRST_PIN+1,GET_BIT(data,1));
			GPIO_writePin(DP_PORT,DP_FIRST_PIN+2,GET_BIT(data,2));
			GPIO_writePin(DP_PORT,DP_FIRST_PIN+3,GET_BIT(data,3));
			_delay_ms(1);
#endif
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
}

void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_Clear);
}

void LCD_intgerToString(int data)
{
   char buff[16];
   itoa(data,buff,10);
   LCD_displayString(buff);
}

void LCD_moveCursor(uint8 row,uint8 col){

	uint8 lcd_memory_address;
		switch(row)
		{
			case 0:
				lcd_memory_address=col;
					break;
			case 1:
				lcd_memory_address=col+0x40;
					break;
		}
		LCD_sendCommand(lcd_memory_address | 0x80);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str){
	LCD_moveCursor(row,col);
	LCD_displayString(Str);

}
