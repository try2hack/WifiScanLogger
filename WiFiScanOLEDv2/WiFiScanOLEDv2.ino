#include "ESP8266WiFi.h"
#include <Wire.h>
#include "SSD1306Wire.h"
SSD1306Wire  display(0x3c, D3, D4);//address , SDA , SCL
#define target "testbugV2"

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  display.init();
  display.flipScreenVertically();
}
void loop() {
  display.drawString(0, 0, "target: " + String(target));
  display.display();
  delay(1000);
  display.clear();
  scanner();
}
void scanner() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("nope");
  } else {
    for (int i = 0; i < n; ++i) {
      if (WiFi.SSID(i) == target) {
        Serial.print(WiFi.SSID(i));
        Serial.print(" : ");
        Serial.print(WiFi.RSSI(i));
        Serial.print(" : ");
        Serial.println(WiFi.BSSIDstr(i));

        display.drawString(0, 0, "SSID: " + String(WiFi.SSID(i)));
        display.drawString(0, 16, "RSSI: " + String(WiFi.RSSI(i)));
        display.drawString(0, 32, "MAC: " + String(WiFi.BSSIDstr(i)));
        display.drawString(0, 48, "Found: " + String(n) + " ap");
        display.display();
        delay(5000);
        display.clear();
        scanner();
      } else {
        display.drawString(0, 0, "Not Found.");
        display.display();
        delay(100);
        display.clear();
      }
    }
  }
}
