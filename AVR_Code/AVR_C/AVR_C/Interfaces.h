/* Heder file for Interfaces */

//-------------------------Interface functions prototypes------

#define BV(x)				(1 << x)
#define setBit(P,B)			P |= BV(B)
#define clearBit(P,B)		P &= ~BV(B)
#define toggleBit(P,B)      P ^= BV(B)

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

//--------------------------------------------------------

extern bool backlight;
extern int contrast;
extern int volume;
extern int menuitem;

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