
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>

boolean backlight = true;
int contrast=50;
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

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);


void setup() {
  
  pinMode(2, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(8,OUTPUT);

  digitalWrite(8,LOW); //Turn Backlight ON
  
  Serial.begin(9600);
  
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
    if (menuitem==0)
    {
      menuitem=3;
    }      
  }else if (up && page == 2 ) {
    up = false;
    contrast--;
    setContrast();
  }
  else if (up && page == 3 ) {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=3;
    }      
  }
  else if (up && page == 4 ) {
    up = false;
    menuitem--;
    if (menuitem==0)
    {
      menuitem=3;
    }      
  }


  
  if (down && page == 1) {
    down = false;
    menuitem++;
    if (menuitem==4) 
    {
      menuitem=1;
    }      
  }else if (down && page == 2 ) {
    down = false;
    contrast++;
    setContrast();
  }
  else if (down && page == 3) {
    down = false;
    menuitem++;
    if (menuitem==4) 
    {
      menuitem=1;
    }
  }
  else if (down && page == 4) {
    down = false;
    menuitem++;
    if (menuitem==4) 
    {
      menuitem=1;
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
    //setContrast();
  }

  else if (down && page == 5 ) {
    down = false;
    volume++;
    //setContrast();
  }


  if (middle) {
    middle = false;
    
//    if (page == 1 && menuitem==2) 
//    {
//      if (backlight) 
//      {
//        backlight = false;
//        turnBacklightOff();
//        }
//      else 
//      {
//        backlight = true; 
//        turnBacklightOn();
//       }
//    }

    if (page == 1 && menuitem==2) 
    {
      page = 3;
      menuitem = 1;
    }

    else if(page == 1 && menuitem ==3)
    {
      page = 4;
      menuitem = 1;
      
    }

    else if (page == 1 && menuitem==1) 
    {
      page=2;
    }
    else if (page == 2)
    {
      page=1;
    }
    else if (page == 3 && menuitem==1) 
    {
      page=2;
    }
    else if (page == 4 && menuitem==1) 
    {
      page=5;
    }
    else if (page == 4 && menuitem==2) 
    {
      page=6;
    }
    else if (page == 4 && menuitem==3) 
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
   }

   if (back) {
    back = false;
    if (page == 2) 
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
    
   }
   
  }

  void checkIfDownButtonIsPressed()
  {
    if (downButtonState != lastDownButtonState) 
  {
    if (downButtonState == 0) 
    {
      down=true;
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
      up=true;
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
      middle=true;
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
      back=true;
    }
    delay(20);
  }
   lastBackButtonState = backButtonState;
}

  
  void drawMenu()
  {
    
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("MAIN MENU");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Date & Time");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print(">Alarm ");
    
    if (backlight) 
    {
      display.print("ON");
    }
    else 
    {
      display.print("OFF");
    }
    display.setCursor(0, 35);
  
    if (menuitem==3) 
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
    
 
  else if (page==2) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Alarm");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.print("Value");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(contrast);
 
    display.setTextSize(2);
    display.display();
  }

  else if (page==3)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Alarm");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Set New Alarm");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print(">Manage Alarms");
    display.setCursor(0, 35);
    
    if (menuitem==3) 
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


  else if (page==4)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Settings");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.print(">Volume");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print(">Contrast");
    display.setCursor(0, 35);

    if (menuitem==3) 
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
  else if (page==5) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Volume");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.print("Value");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(volume);
 
    display.setTextSize(2);
    display.display();
  }
  else if (page==6) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(15, 0);
    display.print("Contrast");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 15);
    display.print("Value");
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(contrast);
 
    display.setTextSize(2);
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
    digitalWrite(8,LOW);
  }

    void turnBacklightOff()
  {
    digitalWrite(8,HIGH);
  }
