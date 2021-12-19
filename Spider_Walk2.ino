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

#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "ASUS2.4";
const char * password = "ComboLevel!";

AsyncUDP udp;

String Poruka;
String PorukaP;


void commListen() {
  if (udp.listen(1234)) {
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print(":");
      PorukaP = String( (char*) packet.data()); // Board: 211021212
  
      if (PorukaP.startsWith("SBoard:", 0)) {
         PorukaP = PorukaP.substring(7); // Rješavamo se prvog dijela "Board: " kako bi ostalo samo "211021212"
        Serial.print("Dobro:");
        Serial.println(PorukaP);
        translateMessage();
        Serial.println("translateMessage done!");
        b = 1; // Oznaka da smo primili poruku
      }
    });
  }
}


void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	hexapod.init(ROBOT_USER_MODE);

    WiFi.mode(WIFI_STA); // Make this the Wi-Fi client (the Wi-Fi router (or server) is WIFI_AP)
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");

    while (1) {
      delay(1000);
    }
  }
  if (udp.connect(IPAddress(192, 168, 0, 101), 1234)) {
    Serial.println("UDP connected");
    Serial.println(WiFi.localIP());
    
}

void loop()
{
	// put your main code here, to run repeatedly:

	delay(100);
}






https://www.google.com/search?q=STEMI+hexapod+user+code&newwindow=1&hl=hr&sxsrf=AOaemvL3aePHdR11BZTPp4lR1jG27RhuKg:1639944148969&ei=1I-_YaKpOtbl7_UP66uxsAY&start=10&sa=N&ved=2ahUKEwii48yD1PD0AhXW8rsIHetVDGYQ8NMDegQIGRBN&biw=1548&bih=1602&dpr=1.25
