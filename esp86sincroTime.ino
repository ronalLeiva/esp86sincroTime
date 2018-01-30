#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "ssidWifi";
const char *password = "pass";
int32_t tiempo = -6 * 3600;
WiFiUDP ntpUDP;
uint8_t horas[] = {15, 15, 15, 15};
uint8_t minutos[] = {44, 46, 47, 48};


NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", tiempo, 60000);
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();
  //Serial.println(timeClient.getFormattedTime());
  // Serial.println(timeClient.getHours());
  for (uint8_t i = 0; i < sizeof(horas) + 1; i ++) {
    if (timeClient.getHours() == horas[i] && timeClient.getMinutes() == minutos[i] && timeClient.getSeconds() < 10) {
      Serial.println("yei si funciona");
      Serial.println(timeClient.getMinutes());
    }
  }
  delay(1000);
}