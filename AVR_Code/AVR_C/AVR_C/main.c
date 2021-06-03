/*
 * AVR_C.c
 *
 * Created: 5/17/2021 12:23:07 PM
 * Author : SENIRU
 */ 

#define F_CPU	16000000UL // 16 MHz clock speed


#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include "I2C.h"
#include "LCD_I2C.h"

#define BV(x)				(1 << x)
#define setBit(P,B)			P |= BV(B)
#define clearBit(P,B)		P &= ~BV(B)
#define toggleBit(P,B)      P ^= BV(B)

bool backlight = false;
int contrast = 10;
int volume = 10;

int menuitem = 1;
int page = 0;

volatile bool up = false;
volatile bool down = false;
volatile bool select = false;
volatile bool back = false;

int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int backButtonState = 0;
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;
int lastBackButtonState = 0;

void drawMenu();
void checkIfDownButtonIsPressed();
void checkIfUpButtonIsPressed();
void checkIfSelectButtonIsPressed();
void checkIfBackButtonIsPressed();

//Interface functions
void timeDisplayInt();
void mainMenuInt();
void dateTimeSetInt();
void alarmMenuInt();
void settingMenuInt();
void volumeInt();
void contrastInt();
void setAlarmInt();
void alarmListInt();
void alarmTonesInt();
void alarmTonesInt2();
void alarmListInt2();
void alarmsettingInt2();

void resetDefaults();
void setContrast();
void turnBacklightOn();
void turnBacklightOff();

int main(void)
{
	DDRD = 0x01; //Set PORTD 4,5,6,7 pins as input pins & Set PORTD0 pin as output
    PORTD = 0xF0; //Set PD0, PD1, PD6, PD7 to INPUT PULL_UP and LOW pin0
	//clearBit(PORTD,0);   //Turn backlight off 
	i2c_init();
	i2c_start();
	i2c_write(0x4E);
	lcdInit();

    while (1) 
    {
		drawMenu();

		downButtonState = digitalRead(7);
		selectButtonState = digitalRead(6);
		upButtonState =   digitalRead(5);
		backButtonState =   digitalRead(4);

		checkIfDownButtonIsPressed();
		checkIfUpButtonIsPressed();
		checkIfSelectButtonIsPressed();
		checkIfBackButtonIsPressed();

        // UP button functions
 		if (up && page == 1 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 3;
			}
			} else if (up && page == 2 ) {
			up = false;
			contrast--;
			setContrast();
		}
		else if (up && page == 3 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 3;
			}
		}
		else if (up && page == 4 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 3;
			}
		}
		else if (up && page == 8 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 3;
			}
		}
		else if (up && page == 9 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 3;
			}
		}
		else if (up && page == 10 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				lcdClear();
				menuitem = 3;
				page = 9;
			}
		}
		else if (up && page == 11 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				lcdClear();
				menuitem = 3;
				page = 8;
			}
		}
		else if (up && page == 12 ) {
			up = false;
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 2;
			}
		}


        // DOWN button functions
		if (down && page == 1) {
			down = false;
			menuitem++;
			if (menuitem == 4)
			{
				menuitem = 1;
			}
			} else if (down && page == 2 ) {
			down = false;
			contrast++;
			setContrast();
		}
		else if (down && page == 3) {
			down = false;
			menuitem++;
			if (menuitem == 4)
			{
				menuitem = 1;
			}
		}
		else if (down && page == 4) {
			down = false;
			menuitem++;
			if (menuitem == 4)
			{
				menuitem = 1;
			}
		}

		else if (down && page == 8) {
			down = false;
			menuitem++;
			if (menuitem == 4)
			{
				lcdClear();
				page = 11;
				menuitem = 1;
			}
		}

		else if (down && page == 9) {
			down = false;
			menuitem++;
			if (menuitem == 4)
			{
				lcdClear();
				page = 10;
				menuitem = 1;
			}
		}
		else if (down && page == 10 ) {
			down = false;
			menuitem++;
			if (menuitem == 5)
			{
				menuitem = 4;
			}
		}
		else if (down && page == 11 ) {
			down = false;
			menuitem++;
			if (menuitem == 5)
			{
				menuitem = 4;
			}
		}
		else if (down && page == 12 ) {
			down = false;
			menuitem++;
			if (menuitem == 3)
			{
				menuitem = 0;
			}
		}

		else if (up && page == 6 ) {
			up = false;
			contrast--;
			//setContrast();
		}

		else if (down && page == 6 ) {
			down = false;
			contrast++;
			//setContrast();
		}

		else if (up && page == 5 ) {
			up = false;
			volume--;
		}

		else if (down && page == 5 ) {
			down = false;
			volume++;
		}

        //SELECT button functions
		if (select) {
			select = false;

			if (page == 0)
			{
				lcdClear();
				page = 1;
				menuitem = 1;
				
			}
			else if (page == 1 && menuitem == 2)
			{
				lcdClear();
				page = 3;
				menuitem = 1;
			}

			else if (page == 1 && menuitem == 3)
			{
				lcdClear();
				page = 4;
				menuitem = 1;

			}

			else if (page == 1 && menuitem == 1)
			{
				lcdClear();
				page = 2;
			}
			else if (page == 2)
			{
				lcdClear();
				page = 1;
			}
			else if (page == 3 && menuitem == 1)
			{
				lcdClear();
				page = 7;
			}
			else if (page == 3 && menuitem == 2)
			{
				lcdClear();
				page = 8;
				menuitem = 1;
			}
			else if (page == 3 && menuitem == 3)
			{
				lcdClear();
				page = 9;
				menuitem = 1;
			}
			else if (page == 4 && menuitem == 1)
			{
				lcdClear();
				page = 5;
			}
			else if (page == 4 && menuitem == 2)
			{
				lcdClear();
				page = 6;
			}
			else if (page == 4 && menuitem == 3)
			{
				resetDefaults();
			}
			else if (page == 5)
			{
				lcdClear();
				page = 4;
				menuitem = 1;
			}
			else if (page == 6)
			{
				lcdClear();
				page = 4;
				menuitem = 2;
			}
			else if (page == 7)
			{
				lcdClear();
				page = 3;
				menuitem = 1;
			}else if (page == 8 || page ==11)
			{
				lcdClear();
				page = 12;
				menuitem = 1;
			}else if (page == 12 && menuitem == 1)
			{
				lcdClear();
				page = 7;
			}
		}
		
		//BACK button functions 
		if (back) {
			back = false;
			if (page == 0)
			{
				if (backlight)
				{
					backlight = false;
					turnBacklightOff();
				}
				else
				{
					backlight = true;
					turnBacklightOn();
				}
			}
			else if (page == 1)
			{
				lcdClear();
				page = 0;
			}
			else if (page == 2)
			{
				lcdClear();
				page = 1;
				menuitem = 1;
			}
			else if (page == 3)
			{
				lcdClear();
				page = 1;
				menuitem = 2;
			}
			else if (page == 4)
			{
				lcdClear();
				page = 1;
				menuitem = 3;
			}
			else if (page == 5)
			{
				lcdClear();
				page = 4;
				menuitem = 1;
			}
			else if (page == 6)
			{
				lcdClear();
				page = 4;
				menuitem = 2;
			}

			else if (page == 7)
			{
				lcdClear();
				page = 3;
				menuitem = 1;
			}
			else if (page == 8)
			{
				lcdClear();
				page = 3;
				menuitem = 2;
			}
			else if (page == 9)
			{
				lcdClear();
				page = 3;
				menuitem = 3;
			}
			else if (page == 10)
			{
				lcdClear();
				page = 9;
				menuitem = 1;
			}
			else if (page == 11)
			{
				lcdClear();
				page = 8;
				menuitem = 1;
			}
			else if (page == 12)
			{
				lcdClear();
				page = 8;
				menuitem = 1;
			}

		}

	}
}

void checkIfDownButtonIsPressed()
{
	if (downButtonState != lastDownButtonState)
	{
		if (downButtonState == 0)
		{
			down = true;
		}
		_delay_ms(20);
	}
	lastDownButtonState = downButtonState;
}

void checkIfUpButtonIsPressed()
{
	if (upButtonState != lastUpButtonState)
	{
		if (upButtonState == 0) {
			up = true;
		}
		_delay_ms(20);
	}
	lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
	if (selectButtonState != lastSelectButtonState)
	{
		if (selectButtonState == 0) {
			select = true;
		}
		_delay_ms(20);
	}
	lastSelectButtonState = selectButtonState;
}

void checkIfBackButtonIsPressed()
{
	if (backButtonState != lastBackButtonState)
	{
		if (backButtonState == 0) {
			back = true;
		}
		_delay_ms(20);
	}
	lastBackButtonState = backButtonState;
}

void drawMenu()
{
	switch(page){
		case 0:
		timeDisplayInt();
		break;
		case 1:
		mainMenuInt();
		break;
		case 2:
		dateTimeSetInt();
		break;
		case 3:
		alarmMenuInt();
		break;
		case 4:
		settingMenuInt();
		break;
		case 5:
		volumeInt();
		break;
		case 6:
		contrastInt();
		break;
		case 7:
		setAlarmInt();
		break;
		case 8:
		alarmListInt();
		break;
		case 9:
		alarmTonesInt();
		break;
		case 10:
		alarmTonesInt2();
		break;
		case 11:
		alarmListInt2();
		break;
		case 12:
		alarmsettingInt2();
		break;
		
	}
	
}

void timeDisplayInt(){
	lcdSetCursor(6, 1);
	lcdPrint("12:34");
	lcdSetCursor(4, 2);
	lcdPrint("29-04-2021");
}
void mainMenuInt(){
	lcdSetCursor(4, 0);
	lcdPrint("MAIN MENU");
	lcdSetCursor(0, 1);

	if (menuitem == 1)
	{
		lcdPrint(">Date & Time");
	}
	else
	{
		lcdPrint(" Date & Time");
	}
	lcdSetCursor(0, 2);

	if (menuitem == 2)
	{
		lcdPrint(">Alarm");
	}
	else
	{
		lcdPrint(" Alarm");
	}
	
	lcdSetCursor(0, 3);

	if (menuitem == 3)
	{
		lcdPrint(">Settings");
	}
	else
	{
		lcdPrint(" Settings");
	}
	//lcd.display();
}

void dateTimeSetInt(){
	
	lcdSetCursor(6, 1);
	lcdPrint("12:34");
	lcdSetCursor(4, 2);
	lcdPrint("29-04-2021");
}

void alarmMenuInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("ALARM MENU");
	lcdSetCursor(0, 1);

	if (menuitem == 1)
	{
		lcdPrint(">Set New Alarm");
	}
	else
	{
		lcdPrint(" Set New Alarm");
	}
	lcdSetCursor(0, 2);

	if (menuitem == 2)
	{
		lcdPrint(">Manage Alarms");
	}
	else
	{
		lcdPrint(" Manage Alarms");
	}
	
	lcdSetCursor(0, 3);

	if (menuitem == 3)
	{
		lcdPrint(">Alarm Tones");
	}
	else
	{
		lcdPrint(" Alarm Tones");
	}
	//lcd.display();
}

void settingMenuInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("SETTINGS");
	lcdSetCursor(0, 1);

	if (menuitem == 1)
	{
		lcdPrint(">Volume");
	}
	else
	{
		lcdPrint(" Volume");
	}
	lcdSetCursor(0, 2);

	if (menuitem == 2)
	{
		lcdPrint(">Contrast");
	}
	else
	{
		lcdPrint(" Contrast");
	}
	
	lcdSetCursor(0, 3);

	if (menuitem == 3)
	{
		lcdPrint(">Reset");
	}
	else
	{
		lcdPrint(" Reset");
	}
	//lcdDisplay();
}

void volumeInt(){
	
	lcdSetCursor(5, 0);
	lcdPrint("Volume");
	lcdSetCursor(5, 2);
	char s_volume[10];
	itoa(volume,s_volume,10);
	lcdPrint(s_volume);
	//lcd.display();
}

void contrastInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("Contrast");
	lcdSetCursor(5, 2);
	char s_contrast[10];
	itoa(contrast,s_contrast,10);
	lcdPrint(s_contrast);
	//lcd.display();
}

void setAlarmInt(){
	lcdSetCursor(6, 1);
	lcdPrint("12:34");
	lcdSetCursor(4, 2);
	lcdPrint("29-04-2021");
}

void alarmListInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("ALARM LIST");
	lcdSetCursor(0, 1);

	if (menuitem == 1)
	{
		lcdPrint(">Alarm1");
	}
	else
	{
		lcdPrint(" Alarm1");
	}
	lcdSetCursor(0, 2);

	if (menuitem == 2)
	{
		lcdPrint(">Alarm2");
	}
	else
	{
		lcdPrint(" Alarm2");
	}
	
	lcdSetCursor(0, 3);

	if (menuitem == 3)
	{
		lcdPrint(">Alarm3");
	}
	else
	{
		lcdPrint(" Alarm3");
	}
	//lcd.display();
}

void alarmListInt2(){
	
	lcdSetCursor(0, 0);
	if (menuitem == 1)
	{
		lcdPrint(">Alarm4");
	}
	else
	{
		lcdPrint(" Alarm4");
	}
	lcdSetCursor(0, 1);

	if (menuitem == 2)
	{
		lcdPrint(">Alarm5");
	}
	else
	{
		lcdPrint(" Alarm5");
	}
	
	lcdSetCursor(0, 2);

	if (menuitem == 3)
	{
		lcdPrint(">Alarm6");
	}
	else
	{
		lcdPrint(" Alarm6");
	}
	
	lcdSetCursor(0, 3);
	if (menuitem == 4)
	{
		lcdPrint(">Alarm7");
	}
	else
	{
		lcdPrint(" Alarm7");
	}
	//lcd.display();
}

void alarmTonesInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("ALARM TONES");
	lcdSetCursor(0, 1);

	if (menuitem == 1)
	{
		lcdPrint(">Alarmtone1");
	}
	else
	{
		lcdPrint(" Alarmtone1");
	}
	lcdSetCursor(0, 2);

	if (menuitem == 2)
	{
		lcdPrint(">Alarmtone2");
	}
	else
	{
		lcdPrint(" Alarmtone2");
	}
	
	lcdSetCursor(0, 3);

	if (menuitem == 3)
	{
		lcdPrint(">Alarmtone3");
	}
	else
	{
		lcdPrint(" Alarmtone3");
	}
	//lcd.display();
}

void alarmTonesInt2(){
	
	lcdSetCursor(0, 0);
	if (menuitem == 1)
	{
		lcdPrint(">Alarmtone4");
	}
	else
	{
		lcdPrint(" Alarmtone4");
	}
	lcdSetCursor(0, 1);

	if (menuitem == 2)
	{
		lcdPrint(">Alarmtone5");
	}
	else
	{
		lcdPrint(" Alarmtone5");
	}
	
	lcdSetCursor(0, 2);

	if (menuitem == 3)
	{
		lcdPrint(">Alarmtone6");
	}
	else
	{
		lcdPrint(" Alarmtone6");
	}
	
	lcdSetCursor(0, 3);
	if (menuitem == 4)
	{
		lcdPrint(">Alarmtone7");
	}
	else
	{
		lcdPrint(" Alarmtone7");
	}
	//lcd.display();
}

void alarmsettingInt2(){
	lcdSetCursor(2, 0);
	lcdPrint("ALARM SETTINGS");
	lcdSetCursor(0, 1);

	if (menuitem == 1)
	{
		lcdPrint(">Edit Alarm");
	}
	else
	{
		lcdPrint(" Edit Alarm");
	}
	
	lcdSetCursor(0, 2);
	if (menuitem == 2)
	{
		lcdPrint(">Delete Alarm");
	}
	else
	{
		lcdPrint(" Delete Alarm");
	}
}
void resetDefaults()
{
	volume = 10;
	contrast = 50;
	setContrast();
	backlight = true;
	turnBacklightOn();
}


void setContrast()
{
	//lcd.backlight(contrast);
}

void turnBacklightOn()
{
	setBit(PORTD,0);
}

void turnBacklightOff()
{
	clearBit(PORTD,0);
}

