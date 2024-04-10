// @File		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		10/04/24
//
//
// Copyright (C) 2024  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#include "mc2002.h"

void MC2002_Write(unsigned char data)
{
    for(unsigned char mask = 0x01; mask; mask <<= 1)
    {                        
        if (data & mask) MC2002_DIO = 1; else MC2002_DIO = 0;
		
		MC2002_CLK = 0;
       __asm__ __volatile__("nop");
		MC2002_CLK = 1;
        __asm__ __volatile__("nop");
    }
}

void MC2002_Command(unsigned char data)
{
	MC2002_STB = 0;
	MC2002_Write(data);
	MC2002_STB = 1;
}

void MC2002_Data(unsigned char address, unsigned char data)
{
	MC2002_Command(0x44);
    
	MC2002_STB = 0;
	MC2002_Write(0xC0 | address);
	MC2002_Write(data);
	MC2002_STB = 1;
}

unsigned char MC2002_Read(void)
{
	unsigned char data = 0;
              
	MC2002_DIO = 1;
         
	for (unsigned char i = 0; i < 8; i++) 
	{
		if (MC2002_DIO) data |= 0x80;
		data >>= 1;	
                
		MC2002_CLK = 0;
       __asm__ __volatile__("nop");
		MC2002_CLK = 1;
        __asm__ __volatile__("nop");
	}
        
	MC2002_DIO = 0;
	
	return data;
}

unsigned char MC2002_GetKey(void)
{
	unsigned char keys = 0;

	MC2002_STB = 0;
	
	MC2002_Write(0x42);
	
	for (unsigned char i = 0; i < 5; i++) 
        {
            keys |= MC2002_Read() << i;
	}
	
	MC2002_STB = 1;

	return keys;
}

void MC2002_Clear(void)
{
    for(unsigned char i=0; i<=13; i++) MC2002_Data(i, 0x00);
}

void MC2002_Init(void)
{
    MC2002_CLK_TRIS = 0;
    MC2002_DIO_TRIS = 0;
    MC2002_STB_TRIS = 0;
	
    MC2002_STB = 1;

    // COMMAND1
    // B7 B6 B5 B4 B3 B2 B1 B0
    // 0  0  -  -  -  -  0  0   9 GRIDS
    // 0  0  -  -  -  -  0  1   8 GRIDS
    // 0  0  -  -  -  -  1  0   7 GRIDS
    // 0  0  -  -  -  -  1  1   6 GRIDS
    MC2002_Command( 0x00 | 0x00 );
        
    // COMMAND2
    // B7 B6 B5 B4 B3 B2 B1 B0
    // 0  1  -  -  -  -  0  0   Write data to display mode
    // 0  1  -  -  -  -  0  1   Ignore
    // 0  1  -  -  -  -  1  0   Read key scan data
    // 0  1  -  -  -  -  1  1   Ignore 
    MC2002_Command( 0x40 | 0x04 );
        
    // COMMAND3: [B0..B3] address [0x00..0x0D]
    // B7 B6 B5 B4 B3 B2 B1 B0
    // 0  0  -  -  0  0  0  0   
    // 0  0  -  -  0  0  0  0   
    // 0  0  -  -  0  0  0  0   
    // 0  0  -  -  0  0  0  0    
    MC2002_Command( 0xC0 | 0x00 );
        
    // COMMAND4
    // B7 B6 B5 B4 B3 B2 B1 B0
    // 1  0  -  -  0  0  0  0   Pulse width = 1/16
    // 1  0  -  -  0  0  0  1   Pulse width = 2/16
    // 1  0  -  -  0  0  1  0   Pulse width = 4/16
    // 1  0  -  -  0  0  1  1   Pulse width = 10/16
    // 1  0  -  -  0  1  0  0   Pulse width = 11/16
    // 1  0  -  -  0  1  0  1   Pulse width = 12/16
    // 1  0  -  -  0  1  1  0   Pulse width = 13/16
    // 1  0  -  -  0  1  1  1   Pulse width = 14/16
    // 1  0  -  -  1  0  0  0   Display ON     
    MC2002_Command( 0x80 | 0x08 | 0x07 );
}
