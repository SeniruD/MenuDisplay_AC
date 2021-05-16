#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

boolean backlight = true;
int contrast = 10;
int volume = 10;

int menuitem = 1;
int page = 1;

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;
volatile boolean back = false;

int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int backButtonState = 0;
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;
int lastBackButtonState = 0;

// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal_I2C lcd(0x20, 16, 4);


void setup() {

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, OUTPUT);

  lcd.init();                   // initialize the lcd 
  lcd.init();
  lcd.backlight();
  digitalWrite(8, LOW); //Turn Backlight ON

  
}


void loop() {

  drawMenu();

  downButtonState = digitalRead(7);
  selectButtonState = digitalRead(6);
  upButtonState =   digitalRead(1);
  backButtonState =   digitalRead(0);

  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();
  checkIfBackButtonIsPressed();

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
      lcd.clear();
      menuitem = 3;
      page = 9;
    }
  }
  else if (up && page == 11 ) {
    up = false;
    menuitem--;
    if (menuitem == 0)
    {
      lcd.clear();
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
      lcd.clear();
      page = 11;
      menuitem = 1;
    }
  }

  else if (down && page == 9) {
    down = false;
    menuitem++;
    if (menuitem == 4)
    {
      lcd.clear();
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
    setContrast();
  }

  else if (down && page == 6 ) {
    down = false;
    contrast++;
    setContrast();
  }

  else if (up && page == 5 ) {
    up = false;
    volume--;
  }

  else if (down && page == 5 ) {
    down = false;
    volume++;
  }


  if (middle) {
    middle = false;

  if (page == 0)
    { 
      lcd.clear();
      page = 1;
      menuitem = 1;
      
    }
    else if (page == 1 && menuitem == 2)
    {
      lcd.clear();
      page = 3;
      menuitem = 1;
    }

    else if (page == 1 && menuitem == 3)
    {
      lcd.clear();
      page = 4;
      menuitem = 1;

    }

    else if (page == 1 && menuitem == 1)
    {
      lcd.clear();
      page = 2;
    }
    else if (page == 2)
    {
      lcd.clear();
      page = 1;
    }
    else if (page == 3 && menuitem == 1)
    {
      lcd.clear();
      page = 7;
    }
    else if (page == 3 && menuitem == 2)
    {
      lcd.clear();
      page = 8;
      menuitem = 1;
    }
    else if (page == 3 && menuitem == 3)
    {
      lcd.clear();
      page = 9;
      menuitem = 1;
    }
    else if (page == 4 && menuitem == 1)
    {
      lcd.clear();
      page = 5;
    }
    else if (page == 4 && menuitem == 2)
    {
      lcd.clear();
      page = 6;
    }
    else if (page == 4 && menuitem == 3)
    {
      resetDefaults();
    }
    else if (page == 5)
    {
      lcd.clear();
      page = 4;
      menuitem = 1;
    }
    else if (page == 6)
    {
      lcd.clear();
      page = 4;
      menuitem = 2;
    }
    else if (page == 7)
    {
      lcd.clear();
      page = 3;
      menuitem = 1;
    }else if (page == 8 or page ==11)
    {
      lcd.clear();
      page = 12;
      menuitem = 1;
    }else if (page == 12 && menuitem == 1)
    {
      lcd.clear();
      page = 7;
    }
  }

  if (back) {
    back = false;
    if (page == 0)
    {
      if (backlight)
      {
        backlight = false;
        turnBacklightOff();
//        display.setTextSize(1);
//        display.setCursor(70, 1);
//        display.write(42);
//        display.display();
      }
      else
      {
        backlight = true;
        turnBacklightOn();
//        display.setTextSize(1);
//        display.setCursor(70, 1);
//        display.write(15);
//        display.display();
      }
    }
    else if (page == 1)
    {
      lcd.clear();
      page = 0;
    }
    else if (page == 2)
    {
      lcd.clear();
      page = 1;
      menuitem = 1;
    }
    else if (page == 3)
    {
      lcd.clear();
      page = 1;
      menuitem = 2;
    }
    else if (page == 4)
    {
      lcd.clear();
      page = 1;
      menuitem = 3;
    }
    else if (page == 5)
    {
      lcd.clear();
      page = 4;
      menuitem = 1;
    }
    else if (page == 6)
    {
      lcd.clear();
      page = 4;
      menuitem = 2;
    }

    else if (page == 7)
    {
      lcd.clear();
      page = 3;
      menuitem = 1;
    }
    else if (page == 8)
    {
      lcd.clear();
      page = 3;
      menuitem = 2;
    }
    else if (page == 9)
    {
      lcd.clear();
      page = 3;
      menuitem = 3;
    }
    else if (page == 10)
    {
      lcd.clear();
      page = 9;
      menuitem = 1;
    }
    else if (page == 11)
    {
      lcd.clear();
      page = 8;
      menuitem = 1;
    }
     else if (page == 12)
    {
      lcd.clear();
      page = 8;
      menuitem = 1;
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
    delay(20);
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
    delay(20);
  }
  lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
  if (selectButtonState != lastSelectButtonState)
  {
    if (selectButtonState == 0) {
      middle = true;
    }
    delay(20);
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
    delay(20);
  }
  lastBackButtonState = backButtonState;
}

void drawMenu()
{
  switch(page){
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

void mainMenuInt(){
    lcd.setCursor(4, 0);
    lcd.print("MAIN MENU");
    lcd.setCursor(0, 1);

    if (menuitem == 1)
    {
      lcd.print(">Date & Time");
    }
    else
    {
      lcd.print(" Date & Time");
    }
    lcd.setCursor(0, 2);

    if (menuitem == 2)
    {
      lcd.print(">Alarm");
    }
    else
    {
      lcd.print(" Alarm");
    }
    
    lcd.setCursor(0, 3);

    if (menuitem == 3)
    {
      lcd.print(">Settings");
    }
    else
    {
      lcd.print(" Settings");
    }
    lcd.display();
}

void dateTimeSetInt(){
  
    lcd.setCursor(6, 1);
    lcd.print("12:34");
    lcd.setCursor(4, 2);
    lcd.print("29-04-2021");
}

void alarmMenuInt(){
  
    lcd.setCursor(4, 0);
    lcd.print("ALARM MENU");
    lcd.setCursor(0, 1);

    if (menuitem == 1)
    {
      lcd.print(">Set New Alarm");
    }
    else
    {
      lcd.print(" Set New Alarm");
    }
    lcd.setCursor(0, 2);

    if (menuitem == 2)
    {
      lcd.print(">Manage Alarms");
    }
    else
    {
      lcd.print(" Manage Alarms");
    }
    
    lcd.setCursor(0, 3);

    if (menuitem == 3)
    {
      lcd.print(">Alarm Tones");
    }
    else
    {
      lcd.print(" Alarm Tones");
    }
    lcd.display();
}

void settingMenuInt(){
  
    lcd.setCursor(4, 0);
    lcd.print("SETTINGS");
    lcd.setCursor(0, 1);

    if (menuitem == 1)
    {
      lcd.print(">Volume");
    }
    else
    {
      lcd.print(" Volume");
    }
    lcd.setCursor(0, 2);

    if (menuitem == 2)
    {
      lcd.print(">Contrast");
    }
    else
    {
      lcd.print(" Contrast");
    }
    
    lcd.setCursor(0, 3);

    if (menuitem == 3)
    {
      lcd.print(">Reset");
    }
    else
    {
      lcd.print(" Reset");
    }
    lcd.display();
}

void volumeInt(){
  
    lcd.setCursor(5, 0);
    lcd.print("Volume");
    lcd.setCursor(5, 2);
    lcd.print(volume);
    lcd.display();
}

void contrastInt(){
  
    lcd.setCursor(4, 0);
    lcd.print("Contrast");
    lcd.setCursor(5, 2);
    lcd.print(contrast);
    lcd.display();
}

void setAlarmInt(){
    lcd.setCursor(6, 1);
    lcd.print("12:34");
    lcd.setCursor(4, 2);
    lcd.print("29-04-2021");
}

void alarmListInt(){
  
    lcd.setCursor(4, 0);
    lcd.print("ALARM LIST");
    lcd.setCursor(0, 1);

    if (menuitem == 1)
    {
      lcd.print(">Alarm1");
    }
    else
    {
      lcd.print(" Alarm1");
    }
    lcd.setCursor(0, 2);

    if (menuitem == 2)
    {
      lcd.print(">Alarm2");
    }
    else
    {
      lcd.print(" Alarm2");
    }
    
    lcd.setCursor(0, 3);

    if (menuitem == 3)
    {
      lcd.print(">Alarm3");
    }
    else
    {
      lcd.print(" Alarm3");
    }
    lcd.display();
}

void alarmListInt2(){
  
    lcd.setCursor(0, 0);
    if (menuitem == 1)
    {
      lcd.print(">Alarm4");
    }
    else
    {
      lcd.print(" Alarm4");
    }
    lcd.setCursor(0, 1);

    if (menuitem == 2)
    {
      lcd.print(">Alarm5");
    }
    else
    {
      lcd.print(" Alarm5");
    }
    
    lcd.setCursor(0, 2);

    if (menuitem == 3)
    {
      lcd.print(">Alarm6");
    }
    else
    {
      lcd.print(" Alarm6");
    }
    
    lcd.setCursor(0, 3);
    if (menuitem == 4)
    {
      lcd.print(">Alarm7");
    }
    else
    {
      lcd.print(" Alarm7");
    }
    lcd.display();
}

void alarmTonesInt(){
  
    lcd.setCursor(4, 0);
    lcd.print("ALARM TONES");
    lcd.setCursor(0, 1);

    if (menuitem == 1)
    {
      lcd.print(">Alarmtone1");
    }
    else
    {
      lcd.print(" Alarmtone1");
    }
    lcd.setCursor(0, 2);

    if (menuitem == 2)
    {
      lcd.print(">Alarmtone2");
    }
    else
    {
      lcd.print(" Alarmtone2");
    }
    
    lcd.setCursor(0, 3);

    if (menuitem == 3)
    {
      lcd.print(">Alarmtone3");
    }
    else
    {
      lcd.print(" Alarmtone3");
    }
    lcd.display();
}

void alarmTonesInt2(){
  
    lcd.setCursor(0, 0);
    if (menuitem == 1)
    {
      lcd.print(">Alarmtone4");
    }
    else
    {
      lcd.print(" Alarmtone4");
    }
    lcd.setCursor(0, 1);

    if (menuitem == 2)
    {
      lcd.print(">Alarmtone5");
    }
    else
    {
      lcd.print(" Alarmtone5");
    }
    
    lcd.setCursor(0, 2);

    if (menuitem == 3)
    {
      lcd.print(">Alarmtone6");
    }
    else
    {
      lcd.print(" Alarmtone6");
    }
    
    lcd.setCursor(0, 3);
    if (menuitem == 4)
    {
      lcd.print(">Alarmtone7");
    }
    else
    {
      lcd.print(" Alarmtone7");
    }
    lcd.display();
}

void alarmsettingInt2(){
    lcd.setCursor(2, 0);
    lcd.print("ALARM SETTINGS");
    lcd.setCursor(0, 1);

    if (menuitem == 1)
    {
      lcd.print(">Edit Alarm");
    }
    else
    {
      lcd.print(" Edit Alarm");
    }
    
    lcd.setCursor(0, 2);
    if (menuitem == 2)
    {
      lcd.print(">Delete Alarm");
    }
    else
    {
      lcd.print(" Delete Alarm");
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
  digitalWrite(8, LOW);
}

void turnBacklightOff()
{
  digitalWrite(8, HIGH);
}
