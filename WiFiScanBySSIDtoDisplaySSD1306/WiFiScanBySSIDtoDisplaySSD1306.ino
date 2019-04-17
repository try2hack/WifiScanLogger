#include "ESP8266WiFi.h"
#include <Wire.h>
#include "SSD1306Wire.h"
SSD1306Wire  display(0x3c, D3, D5);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  display.init();
  display.flipScreenVertically();
}
void loop() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("nope");
  } else {
    for (int i = 0; i < n; ++i) {
      if (WiFi.SSID(i) == "RTS") {
        //        Serial.print("ESP8266 #");
        //        Serial.println(device);
        Serial.print(WiFi.SSID(i));
        Serial.print(" : ");
        Serial.print(WiFi.RSSI(i));
        Serial.print(" : ");
        Serial.println(WiFi.BSSIDstr(i));

        display.drawString(0, 0, "SSID: " + String(WiFi.SSID(i)));
        display.drawString(0, 16, "RSSI: " + String(WiFi.RSSI(i)));
        display.drawString(0, 32, "MAC: " + String(WiFi.BSSIDstr(i)));
        display.drawString(0, 48, "Range: " + String("m"));
        display.display();
      }
    }
    delay(5000);
    display.clear();
    
   
  }
}
