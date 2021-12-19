/*

This file is part of STEMI hexapod library.

Copyright (C) 2017 STEMI d.o.o.
Authors: Luka Fucek, et al.
Contact: info@stemi.education
Web: https://www.stemi.education/

STEMI hexapod library is free software exclusively
for non-commercial activities.

In case of developing any comercial activities involving STEMI
hexapod library please contact stemi.education for providing custom
license at: info@stemi.education.

For non-commercial activities you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

STEMI hexapod library is
distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with STEMI hexapod library.
If not, see http://www.gnu.org/licenses/.

For additional information please check http://www.stemi.education.

*/

#include "Hexapod.h"
SharedData robot;
Hexapod  hexapod;


#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.println();


  if ( myData.b == 32 ) { // || OR -
  robot.setHeight(100);
    //return 0;
    if (serialoutput) {
      Serial.print("gumb_A ");
    }
  }

  if ( myData.b == 33 ) { // || OR -
  robot.setHeight(30);
    //return 0;
    if (serialoutput) {
      Serial.print("gumb_B ");
    }
  }



  
}


void setup()
{
	Serial.begin(115200);
	hexapod.init();
	robot.setLed(GREEN);
	robot.setHeight(50);

  
    // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  
}

Color clrArray[7] = {BLUE, YELLOW, GREEN, CYAN, PURPLE, RED, ORANGE};
uint8_t clrCount = 0;

void loop()
{

	int touchPattern = robot.getTouchPattern();
	if (touchPattern == TOUCH_00X)
	{
		robot.writeExtraServo(-80);
		setLEDrandom();
	}
	else if (touchPattern == TOUCH_X00)
	{
		setLEDSequence();
		robot.writeExtraServo(80);
	}
	else if (touchPattern == TOUCH_0X0)
	{
		robot.exitUserMode();
	}
	else if (touchPattern == TOUCH_0XX)
	{
		robot.move(FORWARD,2000);
	}
	else if (touchPattern == TOUCH_XX0)
	{
		robot.move(BACKWARD,2000);
	}
	delay(20);
}


void setLEDrandom()
{
	robot.setLedStatic(0, clrArray[random(0, 6)]);
	robot.setLedStatic(1, clrArray[random(0, 6)]);
	robot.setLedStatic(2, clrArray[random(0, 6)]);
	robot.setLedStatic(3, clrArray[random(0, 6)]);
	robot.setLedStatic(4, clrArray[random(0, 6)]);
	robot.setLedStatic(5, clrArray[random(0, 6)]);
}

void setLEDSequence()
{
	robot.setLedStatic(clrArray[clrCount]);
	clrCount = (clrCount + 1) % 7;
}
