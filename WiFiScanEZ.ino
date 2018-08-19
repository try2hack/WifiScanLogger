/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include "ESP8266WiFi.h"


void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
   WiFi.mode(WIFI_STA);
   WiFi.begin("testbug2","12345678");

  while (WiFi.status() != WL_CONNECTED) 
  {     
    delay(500);
    Serial.println("nope");
  }
  
  Serial.println("Wi-Fi connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks(false,true);
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(" : ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(") ");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.println((WiFi.isHidden(i) == 0)?" ":" Hidden");
      
      
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}
