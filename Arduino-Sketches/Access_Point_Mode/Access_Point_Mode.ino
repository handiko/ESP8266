
/*
 * 
 */

#include <ESP8266WiFi.h>

const char *ssid = "ESP8266 Acces Point";
const char *password = "Metallica";

bool led = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(10);
  Serial.print('\n');

  WiFi.mode(WIFI_AP); // WIFI_STA, WIFI_AP_STA, WIFI_OFF
  WiFi.softAP(ssid, password);
  
  Serial.print("Access Point \"");
  Serial.println(ssid);
  Serial.print("With password \"");
  Serial.print(password);
  Serial.println("\" is started");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  for(int i=0;i<4;i++) {
    led ^= 1;
    digitalWrite(LED_BUILTIN, led);
    delay(75);
  }
  delay(2000);

  //ESP.restart();
  //ESP.reset();
}
