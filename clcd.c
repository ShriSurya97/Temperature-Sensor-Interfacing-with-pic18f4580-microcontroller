/*
 * File:   clcd.c
 * Author: Shrisuryarathinam
 *
 * Created on 5 June, 2024, 12:01 PM
 */


#include <xc.h>
#include "clcd.h"
#include "main.h"

// LCD function definitions
//function initializes the LCD in 4-bit mode.
void Lcd_Init() 
{
    TRISB = 0x00;
    Lcd_Command(0x02);  // Initialize LCD in 4-bit mode
    Lcd_Command(0x28);  // 4-bit mode, 2 line, 5x7 dots
    Lcd_Command(0x0C);  // Display on, cursor off
    Lcd_Command(0x06);  // Auto increment cursor
    Lcd_Command(0x01);  // Clear display
    __delay_ms(2);
}

//function sends commands to the LCD.
void Lcd_Command(char cmd) 
{
    PORTB = (PORTB & 0x0F) | (cmd & 0xF0);  // Send upper nibble
    PORTB &= ~0x01;  // RS = 0 for command
    PORTB |= 0x02;   // E = 1
    __delay_us(1);
    PORTB &= ~0x02;  // E = 0
    __delay_us(100);
    
    PORTB = (PORTB & 0x0F) | (cmd << 4);  // Send lower nibble
    PORTB |= 0x02;   // E = 1
    __delay_us(1);
    PORTB &= ~0x02;  // E = 0
    __delay_ms(2);
}

//function sends a character to the LCD.
void Lcd_Char(char data)
{
    PORTB = (PORTB & 0x0F) | (data & 0xF0);  // Send upper nibble
    PORTB |= 0x01;  // RS = 1 for data
    PORTB |= 0x02;  // E = 1
    __delay_us(1);
    PORTB &= ~0x02;  // E = 0
    __delay_us(100);
    
    PORTB = (PORTB & 0x0F) | (data << 4);  // Send lower nibble
    PORTB |= 0x02;  // E = 1
    __delay_us(1);
    PORTB &= ~0x02;  // E = 0
    __delay_ms(2);
}

// function displays a string on the LCD.
void Lcd_String(const char* str)
{
    while(*str) {
        Lcd_Char(*str++);
    }
}

//function sets the cursor position on the LCD.
void Lcd_Set_Cursor(char row, char col) {
    char pos;
    if (row == 1)
        pos = 0x80 + col - 1;
    else if (row == 2)
        pos = 0xC0 + col - 1;
    Lcd_Command(pos);
}

