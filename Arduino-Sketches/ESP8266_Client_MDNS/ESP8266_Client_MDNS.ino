/*
 * 
 */
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h> 

ESP8266WiFiMulti wifiMulti;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  
  wifiMulti.addAP("My-WiFi", "Metallica");
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
  
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());

  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
}

void loop() {
  
}

/*
 * 
 */
