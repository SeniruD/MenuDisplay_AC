/*
 * AVR_C.c
 *
 * Created: 5/17/2021 12:23:07 PM
 * Author : SENIRU
 */ 

#define F_CPU	8000000UL // 8 MHz clock speed


#include <avr/io.h>
#include <util/delay.h>
#define BV(x)				(1 << x)
#define setBit(P,B)			P |= BV(B)
#define clearBit(P,B)		P &= ~BV(B)
#define toggleBit(P,B)      P ^= BV(B)
#define RS                  PORTB3
#define En                  PORTB2
#define Line1 0x80
#define Line2 0xc0
#define Line3 0x90
#define Line4 0xD0


void LCD_Init();
void LCD_CmdWrite( char cmd);
void LCD_DataWrite( char data);
void LCD_GoToXY(char row, char col);
void LCD_DisplayString(char *string_ptr);
void LCD_Clear();


int main(void)
{
	DDRD = 0x00; //Set PORTD as input pins
    PORTD = 0xF0; //Set PD0, PD1, PD6, PD7 to INPUT PULL_UP
	
	LCD_Init();
	LCD_Clear(0x0C);
	LCD_DisplayString("Seniru");
    while (1) 
    {
		//return 0;
    }
}

void LCD_Init()
{
	_delay_ms(50);
	DDRB = 0xFD;              //Set RS,En,data pins as output
	LCD_CmdWrite(0x02);	      //Initialize the LCD in 4bit Mode
	LCD_CmdWrite(0x28);       //to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	LCD_CmdWrite(0x0C);	      // Display ON cursor OFF
	LCD_CmdWrite(0x01);	      // Clear the LCD
    LCD_CmdWrite(0x80);	      // Move the Cursor to First line First Position
	
	
}

void LCD_CmdWrite( char cmd)
{
	
	PORTB = (cmd & 0xf0);        // Send the Higher Nibble of the command to LCD
	clearBit(PORTB,RS);			 // Register select = 0
	setBit(PORTB,En);            // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);
	
	_delay_us(10);				
	
	PORTB = ((cmd<<4) & 0xf0);   // Send the Lower Nibble of the command to LCD
	clearBit(PORTB,RS);          // Register select = 0
	setBit(PORTB,En);			 // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);	
	_delay_ms(1);

}

void LCD_DataWrite( char data)
{
	PORTB = (data & 0xf0);	  // Send the Higher Nibble of the Data to LCD
	setBit(PORTB,RS);         // Register select = 1
	setBit(PORTB,En);		  // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);
	
	_delay_us(10);
	
	PORTB = ((data <<4) & 0xf0); // Send the Lower Nibble of the Data to LCD
	setBit(PORTB,RS);            // Register select = 1
	setBit(PORTB,En);   		 // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);
	_delay_ms(1);
	
}

void LCD_Clear()
{
	LCD_CmdWrite(0x01);	// Clear the LCD and go to First line First Position
	LCD_CmdWrite(Line1);
}

void LCD_DisplayString(char *string_ptr)
{
	while(*string_ptr)
	LCD_DataWrite(*string_ptr++);
}

void LCD_GoToXY(char row, char col)
{
	if (row == 0 && col<16)
	LCD_CmdWrite((col & 0x0F)|0x80);
	else if (row == 1 && col<16)
	LCD_CmdWrite((col & 0x0F)|0xC0);
	else if (row == 2 && col<16)
	LCD_CmdWrite(((col) & 0x0F)| 0x90);
	else if (row == 3 && col<16)
	LCD_CmdWrite(((col) & 0x0F)|0xD0);
	LCD_CmdWrite(0x0C); //enable cursor
}
