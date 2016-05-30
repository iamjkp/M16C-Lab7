#include "sfr62p.h"
#include "qsk_led.h"

void InitLED() {
	// SET Direction
	pd8_0 = 1;
	pd7_4 = 1;
	pd7_2 = 1;
	
	// SET Default Color
	p8_0 = 1; // RED
	p7_4 = 1; // YELLOW
	p7_2 = 1; // GREEN
	
}

void OnLED(unsigned char color) {
	switch( color ) {
		case R_LED:
		p8_0 = 1;
		break;
		case Y_LED:
		p7_4 = 1;
		break;
		case G_LED:
		p7_2 = 1;
		break;
	}
}

void OffLED(unsigned char color) {
	switch( color ) {
		case R_LED:
		p8_0 = 0;
		break;
		case Y_LED:
		p7_4 = 0;
		break;
		case G_LED:
		p7_2 = 0;
		break;
	}
}

void Delay(unsigned long int delay) {
	unsigned long int c = delay * 0x100;	
	while(c--) {
		_asm ("NOP");
		_asm ("NOP");
		_asm ("NOP");
	}
}