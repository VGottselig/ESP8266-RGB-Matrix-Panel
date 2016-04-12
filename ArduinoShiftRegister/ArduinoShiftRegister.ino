/*
Name:    ArduinoSHiftRegister.ino
Created: 30.03.2016 18:12:11
Author:  Vitali Gottselig
*/

#include "TimerOne.h"
#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)

#define LAT 10
#define OE  A0
#define A   A1
#define B   A2
#define C   A3
#define D   A4



#define DATAPORT PORTD 
#define DATADIR  DDRD
#define SCLKPORT PORTB //D13  D12 D11 D10 D9  D8 => D13 = 5
#define SELECTPORT PORTC //A5 A4  A3  A2  A1  A0

#define CLKIN 8

volatile unsigned long currentMillis = 0;


void setup() {
	pinMode(13, OUTPUT);
	pinMode(A, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(C, OUTPUT);
	pinMode(D, OUTPUT);
	pinMode(OE, OUTPUT);
	pinMode(CLKIN, INPUT);
}

volatile byte row = 0;

void loop() {
	while (true)
	{
		currentMillis = micros();
		while ((byte)(PINB & 1) == (byte)(row % 2)) {}
		if (micros() - currentMillis > 300) row = 30;
		SELECTPORT = row;
		row++;
		if (row >= 32) row = 0;
	}
}
