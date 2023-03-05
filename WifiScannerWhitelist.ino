#include "ESP8266WiFi.h"
#include <cmath>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// OLED display
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

// Reference RSSI at a reference distance of 1 meter
const int REF_RSSI = -30;

// Path loss exponent (depends on environment)
const double PATH_LOSS_EXP = 2.5;

// List of MAC addresses to allow during the WiFi network scan
const char* WHITELIST[] = {
  "00:11:22:33:44:55",
  "66:77:88:99:aa:bb"
};
const int WHITELIST_SIZE = sizeof(WHITELIST) / sizeof(WHITELIST[0]);

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  Serial.println("Starting WiFi scan...");

  // Perform a WiFi network scan and get the number of networks found
  int n = WiFi.scanNetworks(false, true);
  Serial.print("Found ");
  Serial.print(n);
  Serial.println(" networks");

  if (n == 0) {
    Serial.println("No networks found");
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    int count = 0;
    // Loop over all the networks found and calculate their distance based on the RSSI value
    for (int i = 0; i < n && count < 10; i++) {
      String ssid = WiFi.SSID(i);
      String mac = WiFi.BSSIDstr(i);
      int rssi = WiFi.RSSI(i);

      // Check if the MAC address is in the whitelist
      bool whitelisted = false;
      for (int j = 0; j < WHITELIST_SIZE; j++) {
        if (strcmp(mac.c_str(), WHITELIST[j]) == 0) {
          whitelisted = true;
          break;
        }
      }

      double distance = std::pow(10.0, (REF_RSSI - rssi) / (10.0 * PATH_LOSS_EXP));

      if (!whitelisted) {
        display.setCursor(0, count * 8);
        display.print(ssid + " " + mac + " " + String(distance, 2) + "m");
        count++;
      }
    }
    display.display();
  }

  // Wait before performing the next scan
  delay(5000);
}
