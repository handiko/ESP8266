/*
 *
 */
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>

ESP8266WiFiMulti wifiMulti;
WiFiUDP UDP;

IPAddress timeServerIP;
const char* NTPServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48;
byte NTPBuffer[NTP_PACKET_SIZE];

void startWiFi();
void starUDP();

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.flush();
  Serial.println("\r\n");

  startWiFi();
  startUDP();

  if(!WiFi.hostByName(NTPServerName, timeServerIP)) {
    Serial.println("DNS lookup failed. Rebooting.");
    Serial.flush();
    ESP.reset();
  }

  Serial.print("Time server IP: ");
  Serial.println(timeServerIP);

  Serial.println("\r\nSending NTP request ...");
  sendNTPpacket(timeServerIP);
}

unsigned long intervalNTP = 60000;
unsigned long prevNTP = 0;
unsigned long lastNTPResponse = millis();
uint32_t timeUNIX = 0;

unsigned long prevActualTime = 0;

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - prevNTP > intervalNTP) {
    prevNTP = currentMillis;
    Serial.println("\r\nSending NTP request");
    sendNTPpacket(timeServerIP);
  }

  uint32_t time = getTime();

  if(time) {
    timeUNIX = time;
    Serial.print("NTP response: ");
    Serial.println(timeUNIX);
    lastNTPResponse = currentMillis;
  }
  else if((currentMillis - lastNTPResponse) > 3600000) {
    Serial.println("More than 1 hour since last NTP Response. Rebooting.");
    Serial.flush();
    ESP.reset();
  }

  uint32_t actualTime = timeUNIX + (currentMillis - lastNTPResponse)/1000;

  if(actualTime != prevActualTime && timeUNIX != 0) {
    prevActualTime = actualTime;
    Serial.printf("\nUTC time:\t%d:%d:%d ", getHours(actualTime), getMinutes(actualTime), getSeconds(actualTime));
  }
}

void startWiFi() {
  wifiMulti.addAP("YC1SDL", "Metallica");
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
  
  Serial.println("Connecting");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(250);
    Serial.print('.');
  }

  Serial.println("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println("\r\n");
}

void startUDP() {
  Serial.println("Starting UDP");
  UDP.begin(123);
  Serial.print("Local port: ");
  Serial.println(UDP.localPort());
  Serial.println();
}

uint32_t getTime() {
  if (UDP.parsePacket() == 0) {
    return 0;
  }
  UDP.read(NTPBuffer, NTP_PACKET_SIZE);
  uint32_t NTPTime = (NTPBuffer[40] << 24) | (NTPBuffer[41] << 16) | (NTPBuffer[42] << 8) | NTPBuffer[43];
  const uint32_t seventyYears = 2208988800UL;
  uint32_t UNIXTime = NTPTime - seventyYears;
  return UNIXTime;
}

void sendNTPpacket(IPAddress& address) {
  memset(NTPBuffer, 0, NTP_PACKET_SIZE);
  NTPBuffer[0] = 0b11100011;
  UDP.beginPacket(address, 123);
  UDP.write(NTPBuffer, NTP_PACKET_SIZE);
  UDP.endPacket();
}

inline int getSeconds(uint32_t UNIXTime) {
  return UNIXTime % 60;
}
inline int getMinutes(uint32_t UNIXTime) {
  return UNIXTime / 60 % 60;
}
inline int getHours(uint32_t UNIXTime) {
  return UNIXTime / 3600 % 24;
}

/*
 * 
 */
