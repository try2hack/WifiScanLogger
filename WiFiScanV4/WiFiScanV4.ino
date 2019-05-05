#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
   WiFi.mode(WIFI_STA);
   WiFi.begin("ssid","pwd");

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
//      Serial.print(WiFi.RSSI(i));
      Serial.print(") ");
      Serial.print(WiFi.BSSIDstr(i));
//      Serial.println((WiFi.isHidden(i) == 0)?" ":" Hidden");           
      delay(1000);
       HTTPClient http;
  String host = "host/esp/post.php";
  http.begin(host);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String ssid = WiFi.SSID(i);
  String mac = WiFi.BSSIDstr(i);

  int httpCode = http.POST("ssid="+ssid+"&mac="+mac);
  Serial.println(httpCode);
  if(httpCode == HTTP_CODE_OK)
  {
  Serial.println("pass");
  }
  else
  {
  Serial.println("nope");
  }
  http.end();
    }
  }
  Serial.println("");
 
  // Wait a bit before scanning again
  delay(5000);
  }
