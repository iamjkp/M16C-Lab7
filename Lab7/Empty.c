/***********************************************************************/
/*                                                                     */
/*  FILE        :Empty.c                                               */
/*  DATE        :Mon, Jan 08, 2007                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :Other                                                 */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.0).     */
/*                                                                     */
/***********************************************************************/
     
#include "qsk_bsp.h"
#include "qsk_switch.h"
#include "qsk_led.h"
#include "qsk_lcd.h"
#include <stdio.h>
#include <string.h>

#define I_MASK (0x0040)
#define GET_INT_STATUS(x) {_asm("STC FLG,$$[FB]",x); x &= I_MASK;}
#define DISABLE_INTS {_asm("fclr i");}
#define ENABLE_INTS {_asm("fset i");}

// prototypes

void mcu_init(void);	              

/* *******************************************************************
 Description:
 Entry:
 Returns:
 
 Notes:
 
***********************************************************************/ 

void init_ta(void) {
	pclk0 = 1;
	
	// Set Period
	ta0 = 2999;
	
	_asm("fclr i");
	// Set Mode 
	tmod0_ta0mr = 0;
	tmod1_ta0mr = 0;
	tck0_ta0mr = 1;
	tck1_ta0mr = 0;
	
	// Set ISR
	ilvl0_ta0ic = 0;
	ilvl1_ta0ic = 0;
	ilvl2_ta0ic = 1;
	
	_asm("fset i");
	
	// Set TA0S <= 1
	ta0s = 1;
}

unsigned long counter = 0;

#pragma INTERRUPT /B TimerHandler

void TimerHandler(void) {
	counter ++;
	_asm("fset i");
}

void counting(void) {
	char buf[16] = {0,};

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%ld", counter / 1000);
	DisplayString(LCD_LINE1, buf);
}

#pragma INTERRUPT Switch1Handler
#pragma INTERRUPT Switch2Handler

void InitSwitchInt(void) {
	_asm("fset i");
	
	// S102
	ilvl0_int0ic = 0;
	ilvl1_int0ic = 1;
	ilvl2_int0ic = 0;
	pol_int0ic = 0;
	
	// S101
	ilvl0_int1ic = 1;
	ilvl1_int1ic = 1;
	ilvl2_int1ic = 1;
	pol_int1ic = 0;
} 

void Switch1Handler(void) {
	counter ++;
}

void Switch2Handler(void) {
	
}

void main(void)
{
	
	int a = 0, b = 0, c = 0;
	
	mcu_init();
	InitDisplay();
	init_ta();
	//InitSwitch();
	//InitSwitchInt();
	
	counting();
	
	// Polling
	while (1) {
		if (counter > 0) {
			unsigned long iset = 0;
			//GET_INT_STATUS(iset);
			//DISABLE_INTS;
			counter --;
			//if (iset) {
			//	ENABLE_INTS;
			//}
			counting();	
		}	
	}
}

