/*
 * Project.c
 *
 *  Created on: Mar 20, 2024
 *      Author: PCM
 */

#include "gpio.h"
#include "util/delay.h"
#include <avr/eeprom.h>  /* Include AVR EEPROM header file */
#include "keypad.h"
#include "lcd.h"
#include "adc.h"
#include "lm35.h"
#include "dc.h"

#define Max_Entry 3
#define Pw_Length 3

/* Common Global Variable will be used */
uint8 Admin_PW, User_One_PW, User_Two_PW, User_Three_PW;
uint8 key = 0; //Determine which user is entered
uint16 temp_value; //TEMP Value

/* FN's Used */

uint8 get_Key(void);
uint16 Enter_Pw(void);
void PW_Init(void);
void Main_Menu(void);
void AC(void);
void Timer1_Fast_PWM_Init(unsigned short duty_cycle);
void Door_Servo(void);
void LED_Init(void);
void Users_Remove_Menu(void);

int main(void) {

	uint8 trial = 0; //Password match
	uint16 enteredPassword;
	uint8 internal_usage_buttons; //during modes
	uint8 ext_usage_buttons; //during removing users

	PW_Init(); // PW Intialize
	LCD_init(); //LCD Intialize
	ADC_ConfigType adc_ConfigType = { AREF, DivisonFactor8 };
	ADC_init(&adc_ConfigType);
	DcMotor_Init();
	LED_Init();

	do {
		trial++;
		enteredPassword = Enter_Pw();
		_delay_ms(100);

		if (enteredPassword == Admin_PW) {
			key = 4;
		} else if (enteredPassword == User_One_PW) {
			key = 1;
		} else if (enteredPassword == User_Two_PW) {
			key = 2;
		} else if (enteredPassword == User_Three_PW) {
			key = 3;
		}
		if (trial == Max_Entry) {
			LCD_clearScreen();
			LCD_displayString("System Locked");
			return 0;
		}
	} while (key == 0);

	while (1) {

		while (key == 4) {

			/* Display the main menu */
			Main_Menu();
			AC();

			internal_usage_buttons = get_Key();

			if (internal_usage_buttons == '%') {
				Door_Servo();
			}

			if (internal_usage_buttons == '*') {
				PORTB = PORTB ^ (1 << PC2); //TOGGLE
			}
			if (internal_usage_buttons == '+') { // Remove User
				/* Not Applicable as we are not using application */
				Users_Remove_Menu();

				ext_usage_buttons = get_Key();

				if (ext_usage_buttons == '+') {
					eeprom_update_byte((uint8*) 61, 0); // Write 0 to USER 1
					LCD_clearScreen();
					LCD_displayString("USER 1 removed");

				}
				if (ext_usage_buttons == '-') {
					eeprom_update_byte((uint8*) 62, 0); // Write 0 to USER 2
					LCD_clearScreen();
					LCD_displayString("USER 2 removed");
				}
				if (ext_usage_buttons == '*') {
					eeprom_update_byte((uint8*) 63, 0); // Write 0 to USER 3
					LCD_clearScreen();
					LCD_displayString("USER 3 removed");
				}
			}

		}

		while (key == 1) {

			Main_Menu();
			AC();

			internal_usage_buttons = get_Key();

			if (internal_usage_buttons == '*') {
				PORTB = PORTB ^ (1 << PC2); //TOGGLE
			}

		}

		while (key == 2) {

			Main_Menu();
			AC();

			internal_usage_buttons = get_Key();

			if (internal_usage_buttons == '*') {
				PORTB = PORTB ^ (1 << PC2); //TOGGLE
			}

		}

		while (key == 3) {

			Main_Menu();
			AC();

			internal_usage_buttons = get_Key();

			if (internal_usage_buttons == '*') {
				PORTB = PORTB ^ (1 << PC2); //TOGGLE
			}
		}

	} //end while1

} //end main

uint8 get_Key(void) {

	uint8 key;

	key = KEYPAD_getPressedKey();

	if (key != 13) //Enter Button = ON
			{
		LCD_displayCharacter('*');
	}

	_delay_ms(500);

	return key;
}

uint16 Enter_Pw(void) {
	uint8 res[Pw_Length]; // PW Stored in ARRAY
	uint8 enterbutton = 0; //Enter button
	uint16 result = 0; //Result to store pw , uint16 because if number >>255 entered

	LCD_clearScreen();
	LCD_displayString("Plz enter pass:");
	LCD_moveCursor(1, 0);

	/*PW Entry , Pw_Length Digits Entry*/

	for (int i = 0; i < Pw_Length; i++) {
		res[i] = get_Key();
		result = ((result) * 10) + ((res[i]) % 10);
	}

	/* Waiting Enter button to be pressed , if any other button is pressed it will be ignored but DISPLAYED :(*/

	do {
		enterbutton = get_Key();
	} while (enterbutton != 13);

	return result;
}

void PW_Init(void) {

	/* Initalzing PWs in the internal EEPROM */

	eeprom_update_byte((uint8*) 60, 123); // Write 123 to EEPROM address 60
	_delay_ms(10); // Wait for EEPROM write to complete
	Admin_PW = eeprom_read_byte((uint8*) 60);

	eeprom_update_byte((uint8*) 61, 245); // Write 245 to EEPROM address 61
	_delay_ms(10);
	User_One_PW = eeprom_read_byte((uint8*) 61);

	eeprom_update_byte((uint8*) 62, 216); // Write 216 to EEPROM address 62
	_delay_ms(10);
	User_Two_PW = eeprom_read_byte((uint8*) 62);

	eeprom_update_byte((uint8*) 63, 196); // Write 196 to EEPROM address 63
	_delay_ms(10);
	User_Three_PW = eeprom_read_byte((uint8*) 63);
}

void Main_Menu(void) {
	LCD_clearScreen();
	if (key == 4) { //Only admin can add or remove user and control door
		LCD_displayString("+RemoveUser%Door");
	}
	LCD_moveCursor(1, 0);
	LCD_displayString("X:TurnON/OFFLEDS");

}

void AC(void) {

	/* When the user logged successfully , he can edit the AC */

	temp_value = LM35_getTemperature();

	if (temp_value < 21) {
		DcMotor_Rotate(Stop, 0);
	} else if (temp_value > 28) {
		DcMotor_Rotate(CW, 100);
	}

}

void Timer1_Fast_PWM_Init(unsigned short duty_cycle) {
	TCNT1 = 0;
	ICR1 = 2499;
	OCR1A = duty_cycle;
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);
}

void Door_Servo(void) {

	GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
	Timer1_Fast_PWM_Init(124);
	_delay_ms(1500);
	Timer1_Fast_PWM_Init(187);
	_delay_ms(1500);
	Timer1_Fast_PWM_Init(250);
	_delay_ms(1500);

}

void LED_Init(void) {

	GPIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_OUTPUT);
	GPIO_writePin(PORTB_ID, PIN2_ID, LOGIC_LOW);

}

void Users_Remove_Menu(void) {
	LCD_clearScreen();
	LCD_displayString("+User 1  -User 2");
	LCD_moveCursor(1, 0);
	LCD_displayString("* User 3");
}

