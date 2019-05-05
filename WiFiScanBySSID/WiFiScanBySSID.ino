#include "ESP8266WiFi.h"
#define device "1"
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
}
void loop() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("nope");
  } else {
    for (int i = 0; i < n; ++i) {
      if (WiFi.SSID(i) == "RTS") {
        //        Serial.printa("ESP8266 #");
        //        Serial.println(device);
        Serial.print(WiFi.SSID(i));
        Serial.print(" : ");
        Serial.print(WiFi.RSSI(i));
        Serial.print(" : ");
        Serial.println(WiFi.BSSIDstr(i));

      }
    }
    delay(5000);
  }
}
