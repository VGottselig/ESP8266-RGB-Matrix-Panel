/*
 Name:		EspRGBLibTest.ino
 Created:	08.04.2016 19:12:50
 Author:	Gad
*/

#include "Adafruit_GFX.h"
#include "ESP8266RGBmatrixPanel.h"


extern "C" {
#include "user_interface.h"
}

//G1	R1 |
//GND	B1 |
//G2	R2 |
//GND	B2  |
//B		A   |
//D		C  |
//LAT	CLK|
//GND	OE |
// !!!IMPORTANT for ABCD-Pins see readme IMPORTANT!!!
//CLK MUST BE CONNECTED ON D0!  
//OE connected with LAT

uint8_t CLK = D0;
uint8_t LAT = D1;
uint8_t R1 = D4;
uint8_t G1 = D5;
uint8_t BL1 = D6;
uint8_t R2 = D7;
uint8_t G2 = D8;
uint8_t BL2 = D9;

ESP8266RGBmatrixPanel matrix(R1, G1, BL1, R2, G2, BL2, LAT);

os_timer_t updateTimer;
void updateDisplay(void * pArg)
{
	matrix.updateDisplay();
}

// the setup function runs once when you press reset or power the board
void setup() {
	
	uint16 color = rmask;
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			color = 0;
			if (x == 2 * y) color |= rmask;
			if (x == 0 || y == 0) color |= gmask;
			if (x == 63 || y == 31 || x + 2 * y == 63)color |= bmask;

			matrix.drawPixel(x, y, color);
		}
	}
	

	color = rmask;
	matrix.fillCircle(16, 16, 6, color);

	os_timer_setfn(&updateTimer, updateDisplay, NULL);
	os_timer_arm(&updateTimer, 5, true);
}

// the loop function runs over and over again until power down or reset
void loop() {
	delay(100);
  
}