/*
 * AVR_C.c
 *
 * Created: 5/17/2021 12:23:07 PM
 * Author : SENIRU
 */ 

#define F_CPU				8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BV(x)				(1 << x)
#define setBit(P,B)			P |= BV(B)
#define clearBit(P,B)		P &= ~BV(B)
#define toggleBit(P,B)      P ^= BV(B)
#define RS                  4
#define En                  3
#define Line1 0x80
#define Line2 0xc0
#define Line3 0x90
#define Line4 0xD0

void command_enable();
void data_enable();
void LCD_Init();
void LCD_CmdWrite( char cmd);
void LCD_DataWrite( char data);
void LCD_GoToXY(char row, char col);
void LCD_DisplayString(char *string_ptr);
void LCD_GoToLineOne();
void LCD_Clear();


int main(void)
{
	DDRD = 0x3C; //Set PORTD input output pins
    PORTD = BV(0) | BV(1) | BV(6) | BV(7); //Set PD0, PD1, PD6, PD7 to INPUT PULL_UP
	//DDRB = BV(3) | BV(4) | BV(0); //PORTB pin 3 enable - output & pin 4 register select - output
	setBit(DDRB,RS); // register select output
	setBit(DDRB,En); // enable select output
	setBit(DDRB,PORTB0); // enable pb0 as output
	LCD_Init();
	LCD_GoToLineOne();
	LCD_DisplayString("seniru");
	setBit(PORTB,0);
	_delay_ms(1000);
	clearBit(PORTB,0);
	_delay_ms(1000);
	setBit(PORTB,0);
	
    while (1) 
    {
		//return 0;
    }
}


void command_enable(){
	
	clearBit(PORTB,RS);
	setBit(PORTB,En);
	_delay_ms(10);
	clearBit(PORTB,En);
	
}

void data_enable(){
	
	setBit(PORTB,RS);
	setBit(PORTB,En);
	_delay_ms(10);
	clearBit(PORTB,En);
	
}

void LCD_Init()
{
	_delay_ms(50);
	LCD_CmdWrite(0x02);	      //Initialize the LCD in 4bit Mode
	LCD_CmdWrite(0x28);       //to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	LCD_CmdWrite(0x0C);	      // Display ON cursor OFF
	LCD_CmdWrite(0x01);	      // Clear the LCD
    LCD_CmdWrite(0x80);	      // Move the Cursor to First line First Position
	
}

void LCD_CmdWrite( char cmd)
{
	
	PORTD = (cmd & 0xf0);        // Send the Higher Nibble of the command to LCD
	clearBit(PORTB,RS);			 // Register select = 0
	setBit(PORTB,En);            // Enable high to low
	_delay_ms(10);
	clearBit(PORTB,En);
	
	_delay_us(10);				
	
	PORTD = ((cmd<<4) & 0xf0);   // Send the Lower Nibble of the command to LCD
	clearBit(PORTB,RS);          // Register select = 0
	setBit(PORTB,En);			 // Enable high to low
	_delay_ms(10);
	clearBit(PORTB,En);	
	_delay_ms(1);

}

void LCD_DataWrite( char data)
{
	PORTD = (data & 0xf0);	  // Send the Higher Nibble of the Data to LCD
	setBit(PORTB,RS);         // Register select = 1
	setBit(PORTB,En);		  // Enable high to low
	_delay_ms(10);
	clearBit(PORTB,En);
	
	_delay_us(10);
	
	PORTD = ((data <<4) & 0xf0); // Send the Lower Nibble of the Data to LCD
	setBit(PORTB,RS);            // Register select = 1
	setBit(PORTB,En);   		 // Enable high to low
	_delay_ms(10);
	clearBit(PORTB,En);
	_delay_ms(1);
	
}

void LCD_Clear()
{
	LCD_CmdWrite(0x01);	// Clear the LCD and go to First line First Position
	LCD_CmdWrite(Line1);
}

void LCD_GoToLineOne()
{
	LCD_CmdWrite(Line1);	// Move the Cursor to First line First Position
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
