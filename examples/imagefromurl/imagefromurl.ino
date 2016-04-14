/*
Name:		imageFromUrl.ino
Created:	08.04.2016 19:12:50
Author:	Gad
https://github.com/VGottselig/ESP8266-RGB-Matrix-Panel
*/
#include <HttpClient.h>
// !!!Remove include file and set ssid and password or create your own wifisettings.h 
#include "wifisettings.h"
const char* ssid = MYSSID;
const char* password = MYWIFIPASS;


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
// !!!IMPORTANT for ABCD-Pins see readme
//CLK MUST BE CONNECTED ON D0!  
//OE connected with LAT

uint8_t CLK = D0;
uint8_t LAT = D1;
uint8_t R1 = D3;
uint8_t G1 = D4;
uint8_t BL1 = D5;
uint8_t R2 = D6;
uint8_t G2 = D7;
uint8_t BL2 = D8;

ESP8266RGBmatrixPanel matrix(R1, G1, BL1, R2, G2, BL2, LAT);

os_timer_t updateTimer;
void updateDisplay(void * pArg)
{
	matrix.updateDisplay();
}

void wificonnect()
{
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}

void showImg(String command) {
	WiFiClient client;

	//https://7wufkg-dm2306.files.1drv.com/y3mA_rOlDRL70twLYBbXYiYEPc-dNS_JzUTnKXQPGjCK_kWUrD2NMELb00E0RGfBf6zgZQHaESy_QgywUBFsm3wLR56I7GX5PmqHbJ9AfP5ozaCMaMb3RNZUcOBh_myA2YYylD7x1MtpEWHIKB9zn0laPgmAXFgMFGl1xMmsCLxwpQ/github.bmp
	const char* host = "7wufkg-dm2306.files.1drv.com";
	command = "y3mA_rOlDRL70twLYBbXYiYEPc-dNS_JzUTnKXQPGjCK_kWUrD2NMELb00E0RGfBf6zgZQHaESy_QgywUBFsm3wLR56I7GX5PmqHbJ9AfP5ozaCMaMb3RNZUcOBh_myA2YYylD7x1MtpEWHIKB9zn0laPgmAXFgMFGl1xMmsCLxwpQ/github.bmp";
	const int httpPort = 80;

	int err = 0;
	if (!client.connect(host, httpPort)) {
		Serial.println("connection error");
		return;
	}

	String request = String("GET ") + "/" + command + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";
	//Serial.println(request);
	// This will send the request to the server
	client.print(request);
	int timeout = millis() + 5000;
	while (client.available() == 0) {
		if (timeout - millis() < 0) {
			client.stop();
			return;
		}
	}

	String bytes;
	while (client.available()) {
		bytes = client.readStringUntil('\r\n');
		while (client.available() && bytes.length() > 1) {
			bytes = client.readStringUntil('\r\n');
		}
		bytes = client.readString();
	}	
	matrix.drawBitmap(&bytes);
}

// the setup function runs once when you press reset or power the board
void setup() {

	os_timer_setfn(&updateTimer, updateDisplay, NULL);
	os_timer_arm(&updateTimer, 2, true);
	matrix.fillScreen(0);
	Serial.begin(115200);
	Serial.println("Start");
	wificonnect();
	showImg("rgb.bmp");
}

// the loop function runs over and over again until power down or reset
void loop() {
	delay(100);

}