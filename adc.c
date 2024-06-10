/*
 * File:   adc.c
 * Author: Shrisuryarathinam
 *
 * Created on 5 June, 2024, 12:12 PM
 */


#include <xc.h>
#include "adc.h"
#include "main.h"

// ADC function definitions
void ADC_Init() 
{
    ADCON0 = 0x01;              // ADC ON, Channel 0 selected
    ADCON1 = 0x0E;              // All AN0 is analog, rest are digital
    ADCON2 = 0xA9;              // Right justified, 20TAD, Fosc/8
}

unsigned int ADC_Read(unsigned char channel)
{
    unsigned short reg_val;

	/*select the channel*/
	ADCON0 = (ADCON0 & 0xC3) | (channel << 2);

	/* Start the conversion */
	GO = 1;
	while (GO);
	reg_val = (ADRESH << 8) | ADRESL; 

	return reg_val;
}