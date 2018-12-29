
/*
 * 
 */
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPmDNS.h>

extern "C" {
  #include <user_interface.h>
}

const char *ssid = "ESP8266 Acces Point";
const char *password = "Metallica";

bool led = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(10);
  Serial.print('\n');

  WiFi.mode(WIFI_AP);               // WIFI_STA, WIFI_AP_STA, WIFI_OFF
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  
  Serial.print("Access Point \"");
  Serial.println(ssid);
  Serial.print("With password \"");
  Serial.print(password);
  Serial.println("\" is started");
  Serial.print("IP address:\t");
  Serial.println(myIP);

  if(!MDNS.begin("esp8266")) {
    Serial.println("Error setting up mDNS responder!");
  }
  Serial.println("mDNS responder started!");
}

void loop() {
  for(int i=0;i<4;i++) {
    led ^= 1;
    digitalWrite(LED_BUILTIN, led);
    delay(75);
  }
  
  client_status();
  
  delay(5000);

  //ESP.restart();
  //ESP.reset();
}

void client_status() {
 
  unsigned char number_client;
  struct station_info *stat_info;
  
  struct ip4_addr *IPaddress;
  IPAddress address;
  int i=1;
  
  number_client= wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();
  
  Serial.print(" Total Connected Clients are = ");
  Serial.println(number_client);
  
  while (stat_info != NULL) {
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;
    
    Serial.print(" client= ");
      
    Serial.print(i);
    Serial.print(" IP adress is = ");
    Serial.print((address));
    Serial.print(" with MAC adress is = ");
      
    Serial.print(stat_info->bssid[0],HEX);Serial.print(" ");
    Serial.print(stat_info->bssid[1],HEX);Serial.print(" ");
    Serial.print(stat_info->bssid[2],HEX);Serial.print(" ");
    Serial.print(stat_info->bssid[3],HEX);Serial.print(" ");
    Serial.print(stat_info->bssid[4],HEX);Serial.print(" ");
    Serial.print(stat_info->bssid[5],HEX);Serial.print(" ");
      
    stat_info = STAILQ_NEXT(stat_info, next);
    i++;
    Serial.println();
  }
  
  delay(500);
}
