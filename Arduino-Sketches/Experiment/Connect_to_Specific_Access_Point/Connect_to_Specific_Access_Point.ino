
/*
 * 
 */

#include <ESP8266WiFi.h>

const char* ssid = "My-WiFi";
const char* password = "Metallica";

bool led = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, led);
  
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  digitalWrite(LED_BUILTIN, 0);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int i=0;
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(++i);
    Serial.print(' ');
  }

  Serial.println("...");
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_BUILTIN, 1);
}

void loop() {
  for(int i=0;i<4;i++) {
    led ^= 1;
    digitalWrite(LED_BUILTIN, led);
    delay(75);
  }
  delay(2000);
}
