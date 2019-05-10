
/*
 * 
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);

void handleRoot();
void handleNotFound();

void setup(void) {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("YC1SDL", "Metallica");
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  
  if (MDNS.begin("esp8266")) {
    Serial.println("mDNS responder started");
  } 
  else {
    Serial.println("Error setting up MDNS responder!");
  }
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Hello world! .... test");
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}
