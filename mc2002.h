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

#ifndef MC2002_H_
#define MC2002_H_

#include <xc.h>

#define MC2002_DIO PORTCbits.RC0
#define MC2002_DIO_TRIS TRISCbits.RC0

#define MC2002_CLK PORTCbits.RC1
#define MC2002_CLK_TRIS TRISCbits.RC1

#define MC2002_STB PORTCbits.RC2
#define MC2002_STB_TRIS TRISCbits.RC2

void MC2002_Clear(void);
void MC2002_Write(unsigned char data);
void MC2002_Command(unsigned char data);
void MC2002_Data(unsigned char address, unsigned char data);
void MC2002_Init(void);

unsigned char MC2002_GetKey(void);
unsigned char MC2002_Read(void);

#endif /* MC2002_H_ */
