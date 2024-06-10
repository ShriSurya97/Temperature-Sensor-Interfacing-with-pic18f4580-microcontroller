#ifndef LCD_H
#define LCD_H

// LCD function prototypes
void Lcd_Init();
void Lcd_Command(char);
void Lcd_Char(char);
void Lcd_String(const char*);
void Lcd_Set_Cursor(char, char);
//bit values --> D0 to D7
//control bit --> Data/Instruction
#endif
