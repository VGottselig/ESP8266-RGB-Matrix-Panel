/*
Author:	Vitali Gottselig
*/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "pins_arduino.h"
#endif
#include "Adafruit_GFX.h"
#include <ESP8266WiFi.h>
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

//typedef unsigned char uint8;
//0b0000RRRRGGGGBBBB
#define rmask 0b0000000000001111
#define gmask 0b0000000011110000
#define bmask 0b0000111100000000

class ESP8266RGBmatrixPanel : public Adafruit_GFX {

 public:
	ESP8266RGBmatrixPanel(uint8 r1, uint8 g1, uint8 b1, uint8 r2, uint8 g2, uint8 b2, uint8 latch);
	void
		drawPixel(int16_t x, int16_t y, uint16_t c),
		fillScreen(uint16_t c),
		updateDisplay(),
		testmuster();
 private:
	 uint16 R1;
	 uint16 G1;
	 uint16 BL1;
	 uint16 R2;
	 uint16 G2;
	 uint16 BL2;
	 uint16 LAT;

	 uint16 pixel[64][32];
	 int layer;
	 volatile uint32_t prts = 0;
	 volatile uint32_t tik = GP16O & ~1;
	 volatile uint32_t tok = GP16O | 1;
	 volatile uint32_t* tikPtr = (volatile uint32_t *)(0x60000000 + (0x768));
	 volatile uint32_t* IOPtr = (volatile uint32_t *)(0x60000000 + (0x300));
};

