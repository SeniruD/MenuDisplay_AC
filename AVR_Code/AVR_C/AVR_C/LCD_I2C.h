/*
 * LCD_I2C.c
 *
 * Created: 04/09/2017 07:37:47 p. m.
 * Author : Seniru
 */ 

#include <avr/io.h>


//-----Proto-Type-------//
void lcdInit();			//----LCD Initializing Function
void toggle();				//----Latching function of LCD
void lcd_cmd_hf(char v1);   //----Function to send half byte command to LCD
void lcdCmdWrite(char cmd);		//----Function to send Command to LCD
void lcdDataWrite(char data);		//----Function to send data to LCD
void lcdPrint(char *c);		//----Function to Send String to LCD
void delay(int ms);			//----Delay function
void lcdDisplay();
void lcdClear();
void lcdSetCursor(char col, char row);
int digitalRead(int x);
//----------------------//

void toggle()
{
	TWDR |= 0x02;					//---PIN En de la LCD en = 1;  -----Latching data in to LCD data register using High to Low signal
	TWCR = (1<<TWINT) | (1<<TWEN);	//---Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));	
	delay(1);
	TWDR &= ~0x02;					//---PIN del Enable de la LCD en = 0;
	TWCR = (1<<TWINT) | (1<<TWEN);	//---Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
}

void lcd_cmd_hf(char v1)
{
	TWDR &=~0x01;					//PIN RS de la LCD rs = 0; ----Selecting register as Command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;					//----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (v1 & 0xF0);			//----Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}

void lcdInit()
{
	lcd_cmd_hf(0x30);       //-----Sequence for initializing LCD
	lcd_cmd_hf(0x30);       //-----     "            "              "               "
	lcd_cmd_hf(0x20);       //-----     "            "              "               "
	lcdCmdWrite(0x28);          //-----Selecting 16 x 4 LCD in 4Bit mode
	lcdCmdWrite(0x0C);          //-----Display ON Cursor OFF
	lcdCmdWrite(0x01);          //-----Clear display
	lcdCmdWrite(0x06);          //-----Cursor Auto Increment
	lcdCmdWrite(0x80);          //-----1st line 1st location of LCD
	
	
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<=ms;i++)
	for(j=0;j<=120;j++);
}

void lcdDisplay()
{
	lcdCmdWrite(0x0C);
}
void lcdCmdWrite( char cmd)
{
	
	TWDR&=~0x01;					//rs = 0; ----Selecting register as command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;                   //----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (cmd & 0xF0);			//----Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
	
	TWDR &= 0x0F;                    //----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= ((cmd & 0x0F)<<4);		//----Masking lower 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}

void lcdDataWrite( char data)
{
	TWDR|=0x01;						//rs = 1; ----Selecting register as command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;				    //----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (data & 0xF0);			//----Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
	
	TWDR &= 0x0F;					//----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= ((data & 0x0F)<<4);		//----Masking lower 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
	
}

void lcdClear()
{
	lcdCmdWrite(0x01);	// Clear the LCD 
	lcdCmdWrite(0x80); // set cursor to line 1 position 1
}

void lcdPrint(char *string_ptr)
{
	while(*string_ptr)
	lcdDataWrite(*string_ptr++);
}

void lcdSetCursor(char col, char row)
{
	if (row == 0 && col<16)
	lcdCmdWrite((col & 0x0F)|0x80);
	else if (row == 1 && col<16)
	lcdCmdWrite((col & 0x0F)|0xC0);
	else if (row == 2 && col<16)
	lcdCmdWrite(((col) & 0x0F)| 0x90);
	else if (row == 3 && col<16)
	lcdCmdWrite(((col) & 0x0F)|0xD0);
	lcdCmdWrite(0x0C); //enable cursor
}

int digitalRead(int x){
	if (~PIND & (1<<x))
		return 1;
	else
		return 0;

}

