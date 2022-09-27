/*
	@File 		
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		20/06/21
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
  
*/

// CONFIG1H
#pragma config OSC = HS         
#pragma config FCMEN = OFF      
#pragma config IESO = OFF       

// CONFIG2L
#pragma config PWRT = OFF       
#pragma config BOREN = OFF      
#pragma config BORV = 3         

// CONFIG2H
#pragma config WDT = OFF        
#pragma config WDTPS = 32768    

// CONFIG3H
#pragma config CCP2MX = PORTC   
#pragma config PBADEN = OFF     
#pragma config LPT1OSC = OFF    
#pragma config MCLRE = ON       

// CONFIG4L
#pragma config STVREN = OFF     
#pragma config LVP = OFF        
#pragma config XINST = OFF      

// CONFIG5L
#pragma config CP0 = OFF        
#pragma config CP1 = OFF        
#pragma config CP2 = OFF        
#pragma config CP3 = OFF        

// CONFIG5H
#pragma config CPB = OFF        
#pragma config CPD = OFF        

// CONFIG6L
#pragma config WRT0 = OFF       
#pragma config WRT1 = OFF       
#pragma config WRT2 = OFF       
#pragma config WRT3 = OFF       

// CONFIG6H
#pragma config WRTC = OFF       
#pragma config WRTB = OFF       
#pragma config WRTD = OFF       

// CONFIG7L
#pragma config EBTR0 = OFF      
#pragma config EBTR1 = OFF      
#pragma config EBTR2 = OFF      
#pragma config EBTR3 = OFF      

// CONFIG7H
#pragma config EBTRB = OFF     

#define _XTAL_FREQ   20000000

#include <xc.h>
#include "mc2002.h"
#include "ds1307.h"
#include "wire.h"

#define INT(h, m) (h * 100 + m)

volatile unsigned char key = 0;

static const unsigned int MC2002_FONT[] =
{
        0x003F, 
	0x0006, 
	0x085B, 
	0x084F, 
	0x0866, 
	0x086D, 
	0x087D, 
	0x0007, 
	0x087F, 
	0x086F, 
	0x0877, 
	0x087C, 
	0x0039, 
	0x085E, 
	0x0879, 
	0x0871, 
};

void Print(int n)
{
    MC2002_Data(0x00, (unsigned char) MC2002_FONT[n/1000%10]);
    MC2002_Data(0x01, MC2002_FONT[n/1000%10] >> 8);
    
    MC2002_Data(0x02, (unsigned char) MC2002_FONT[n/100%10]);
    MC2002_Data(0x03, MC2002_FONT[n/100%10] >> 8);
    
    MC2002_Data(0x04, (unsigned char) MC2002_FONT[n/10%10]);
    MC2002_Data(0x05, MC2002_FONT[n/10%10] >> 8);    
    
    MC2002_Data(0x06, (unsigned char) MC2002_FONT[n/1%10]);
    MC2002_Data(0x07, MC2002_FONT[n/1%10] >> 8);
}

int main(void) 
{
    // WAIT VCC
    __delay_ms(1000);
    
    // DISPLAY INIT
    MC2002_Init();
    
    // DISPLAY CLEAR
    MC2002_Clear();
    
    while(1)
    {
        key = MC2002_GetKey();
        
        if(key != 0xFF)
        {
            Print( INT(0, key) );
        }
    }
    
    return 0;
}
