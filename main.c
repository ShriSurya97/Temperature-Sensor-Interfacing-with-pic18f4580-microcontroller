/*
 * File:   main.c
 * Author: Shrisuryarathinam
 *
 * Created on 5 June, 2024, 12:17 PM
 */


#include <xc.h>
#include <string.h>
#include <stdio.h>
#include "adc.h"
#include "clcd.h"
#include "main.h"


static void init_config()
{
   Lcd_Init();
   ADC_Init();
}

void main(void)
{
    unsigned int adc_value;
    float temperature;
    char temp_str[16];
    
    // Initialize LCD and ADC
    init_config();
    
    while(1) 
    {
        // Read the ADC value from channel 0
        adc_value = ADC_Read(CHANNEL0);

        // Convert the ADC value to voltage
        temperature = (adc_value * 5.0) / 1024.0;
        
        // Convert the voltage to temperature (in Celsius)
        temperature = temperature * 100;
        
        // Format the temperature value as a string
        sprintf(temp_str, "Temp: %.2fC", temperature);
        
        // Display the temperature on the LCD
        Lcd_Set_Cursor(1, 1);
        Lcd_String(temp_str);
        
        __delay_ms(1000);  // Wait for a second
    }
}