#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Fonts/TomThumb.h>
#include <DS3231.h>
#include <Wire.h>


DS3231 clock;
RTCDateTime dt;

extern uint8_t alarmIcon[];

boolean backlight = true;
int contrast = 50;
int volume = 10;

int menuitem = 1;
int page = 0;

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

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);


void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(8, OUTPUT);

  digitalWrite(8, LOW); //Turn Backlight ON

  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);

  display.begin();
  display.setContrast(contrast); //Set contrast to 50
  display.clearDisplay();
  display.display();
}


void loop() {

  drawMenu();

  downButtonState = digitalRead(2);
  selectButtonState = digitalRead(1);
  upButtonState =   digitalRead(0);
  backButtonState =   digitalRead(9);

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
      menuitem = 3;
      page = 9;
    }
  }
  else if (up && page == 11 ) {
    up = false;
    menuitem--;
    if (menuitem == 0)
    {
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
      page = 11;
      menuitem = 1;
    }
  }

  else if (down && page == 9) {
    down = false;
    menuitem++;
    if (menuitem == 4)
    {
      page = 10;
      menuitem = 1;
    }
  }
  else if (down && page == 10 ) {
    down = false;
    menuitem++;
    if (menuitem == 4)
    {
      menuitem = 3;
    }
  }
  else if (down && page == 11 ) {
    down = false;
    menuitem++;
    if (menuitem == 6)
    {
      menuitem = 5;
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
      page = 1;
      menuitem = 1;
    }
    else if (page == 1 && menuitem == 2)
    {
      page = 3;
      menuitem = 1;
    }

    else if (page == 1 && menuitem == 3)
    {
      page = 4;
      menuitem = 1;

    }

    else if (page == 1 && menuitem == 1)
    {
      page = 2;
    }
    else if (page == 2)
    {
      page = 1;
    }
    else if (page == 3 && menuitem == 1)
    {
      page = 7;

    }
    else if (page == 3 && menuitem == 2)
    {
      page = 8;
      menuitem = 1;
    }
    else if (page == 3 && menuitem == 3)
    {
      page = 9;
      menuitem = 1;
    }
    else if (page == 4 && menuitem == 1)
    {
      page = 5;
    }
    else if (page == 4 && menuitem == 2)
    {
      page = 6;
    }
    else if (page == 4 && menuitem == 3)
    {
      resetDefaults();
    }
    else if (page == 5)
    {
      page = 4;
      menuitem = 1;
    }
    else if (page == 6)
    {
      page = 4;
      menuitem = 2;
    }
    else if (page == 7)
    {
      page = 3;
      menuitem = 1;
    }else if (page == 8 or page ==11)
    {
      page = 12;
      menuitem = 1;
    }else if (page == 12 && menuitem == 1)
    {
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
        display.setTextSize(1);
        display.setCursor(70, 1);
        display.write(42);
        display.display();
      }
      else
      {
        backlight = true;
        turnBacklightOn();
        display.setTextSize(1);
        display.setCursor(70, 1);
        display.write(15);
        display.display();
      }
    }
    else if (page == 1)
    {
      page = 0;
    }
    else if (page == 2)
    {
      page = 1;
      menuitem = 1;
    }
    else if (page == 3)
    {
      page = 1;
      menuitem = 2;
    }
    else if (page == 4)
    {
      page = 1;
      menuitem = 3;
    }
    else if (page == 5)
    {
      page = 4;
      menuitem = 1;
    }
    else if (page == 6)
    {
      page = 4;
      menuitem = 2;
    }

    else if (page == 7)
    {
      page = 3;
      menuitem = 1;
    }
    else if (page == 8)
    {
      page = 3;
      menuitem = 2;
    }
    else if (page == 9)
    {
      page = 3;
      menuitem = 3;
    }
    else if (page == 10)
    {
      page = 9;
      menuitem = 1;
    }
    else if (page == 11)
    {
      page = 8;
      menuitem = 1;
    }
     else if (page == 12)
    {
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
  //Main menu Interface

  if (page == 0) {
    dt = clock.getDateTime();

    display.setTextSize(3);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(2, 13);
    display.print(dt.hour);
    display.setCursor(35, 13);
    display.print(":");
    display.setCursor(48, 13);
    display.print(dt.minute);
    display.setTextSize(1);
    display.drawBitmap(1, 0, alarmIcon, 7, 8, BLACK);
    display.setCursor(10, 1);
    display.print(dt.hour);
    display.setCursor(22, 1);
    display.print(":");
    display.setCursor(26, 1);
    display.print(dt.minute);
    display.setFont(&TomThumb);
    display.setCursor(40, 6);
    display.print("PM");
    display.setCursor(50, 6);
    display.print("TUE");
    display.setFont();
    display.drawFastHLine(0, 11, 83, BLACK);
    display.drawFastHLine(0, 37, 83, BLACK);
    display.setCursor(15, 40);
    display.print("03/04/2021");
    if (backlight)
    {

      display.setCursor(70, 1);
      display.write(42);
    }
    else
    {

      display.setCursor(70, 1);
      display.write(15);
    }
    display.display();
  }

  else if (page == 1)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(0, 15);

    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Date & Time");
    display.setCursor(0, 25);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Alarm ");
    display.setCursor(0, 35);

    if (menuitem == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }

    display.print(">Settings");
    display.display();
  }

  //Date and time setting Interface
  else if (page == 2)
  {
    display.setTextSize(3);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(2, 6);
    display.print(dt.hour);
    display.setCursor(35, 6);
    display.print(":");
    display.setCursor(48, 6);
    display.print(dt.minute);
    display.drawFastHLine(0, 31, 83, BLACK);
    display.setTextSize(1);
    display.setCursor(15, 35);
    display.print("29-03-21");
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0, 44);
    display.print("                      ");


    display.display();
  }
  //Alarm Menu Interface
  else if (page == 3)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 0);
    display.print("ALARM MENU");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(0, 15);

    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Set New Alarm");
    display.setCursor(0, 25);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Manage Alarms");
    display.setCursor(0, 35);

    if (menuitem == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Alarm Tones");
    display.display();
  }

  //Setting Menu Interface
  else if (page == 4)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("SETTINGS");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(0, 15);

    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Volume");
    display.setCursor(0, 25);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Contrast");
    display.setCursor(0, 35);

    if (menuitem == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Reset");
    display.display();
  }

  //Volume setting Interface
  else if (page == 5)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Volume");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setTextSize(3);
    display.setCursor(12, 20);
    display.write(17);
    display.setTextSize(2);
    display.setCursor(29, 23);
    display.print(")");
    display.setTextSize(3);
    display.setCursor(40, 20);
    display.print(volume);
    display.display();
  }

  //Contrast setting Interface
  else if (page == 6)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Contrast");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setTextSize(3);
    display.setCursor(8, 20);
    display.write(42);
    display.setCursor(34, 20);
    display.print(contrast);
    display.display();
  }

  //Alarm setup Interface
  else if (page == 7)
  {
    display.setTextSize(3);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(2, 6);
    display.print(dt.hour);
    display.setCursor(35, 6);
    display.print(":");
    display.setCursor(48, 6);
    display.print(dt.minute);
    display.drawFastHLine(0, 31, 83, BLACK);
    display.setTextSize(1);
    display.setCursor(5, 35);
    display.print("S M T W T F S");
    display.drawFastHLine(0, 44, 83, BLACK);
    display.display();
  }
  //Existing alarms interface page 1
  else if (page == 8)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(8, 1);
    display.print("ALARM LIST");
    display.drawFastHLine(0, 11, 83, BLACK);
    display.setCursor(0, 15);
    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }

    display.print("<Alarm1>");
    display.setCursor(0, 25);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarm2>");
    display.setCursor(0, 35);

    if (menuitem == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarm3>");
    display.display();
  }
  
  //Existing alarms interface page 2
  else if (page == 11) {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);

    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarm4>");
    display.setCursor(0, 10);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarm5>");
    display.setCursor(0, 20);


    if (menuitem == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarm6>");
    display.setCursor(0, 30);

    if (menuitem == 4)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarm4>");
    display.setCursor(0, 40);

    if (menuitem == 5)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarm8>");
    display.display();

  }
  //Ringtone interface page 1
  else if (page == 9)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(8, 1);
    display.print("ALARM TONES");
    display.drawFastHLine(0, 11, 83, BLACK);
    display.setCursor(0, 15);
    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }

    display.print("<Alarmtone1>");
    display.setCursor(0, 25);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarmtone2>");
    display.setCursor(0, 35);

    if (menuitem == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarmtone3>");
    display.display();
  }
  
  //Ringtone interface page 1
  else if (page == 10) {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);

    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarmtone4>");
    display.setCursor(0, 10);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarmtone5>");
    display.setCursor(0, 20);


    if (menuitem == 3)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print("<Alarmtone6>");
    display.display();

  }
  //Alarm settings interface
  else if(page = 12){
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 1);
    display.print("ALARM SETTINGS");
    display.drawFastHLine(0, 11, 83, BLACK);
    display.setCursor(0, 15);
    if (menuitem == 1)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Edit Alarm");
    display.setCursor(0, 25);

    if (menuitem == 2)
    {
      display.setTextColor(WHITE, BLACK);
    }
    else
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Delete Alarm");  
    display.display();
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
  display.setContrast(contrast);
  display.display();
}

void turnBacklightOn()
{
  digitalWrite(8, LOW);
}

void turnBacklightOff()
{
  digitalWrite(8, HIGH);
}
