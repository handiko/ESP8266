
/*
 * 
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti  wifiMulti;

bool led = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(10);
  Serial.print('\n');

  wifiMulti.addAP("My-WiFi", "Metallica");
  wifiMulti.addAP("ssid_AP_2", "password_AP_2");
  wifiMulti.addAP("ssid_AP_3", "password_AP_3");

  Serial.println("Connecting ...");

  while(wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop() {
  for(int i=0;i<4;i++) {
    led ^= 1;
    digitalWrite(LED_BUILTIN, led);
    delay(75);
  }
  delay(2000);

  //ESP.reset();
}
