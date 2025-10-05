#include <Arduino.h>
#include <WiFi.h>

const char* SSID = "LAMP";
const char* password = "1234567890";

WiFiServer server(80);
int intensity = 0;

void setup() {
  ledcSetup(0, 5000, 8);
  ledcAttachPin(0, 0);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID, password);

  server.begin();

  delay(2000);
}  

void loop() {
  WiFiClient client = server.available();

  if(client) {
    while(client.connected()) {
      if(client.available()) {
        String line = client.readStringUntil('\n');
        line.trim();

        if(line.equals("UP")) {
          intensity += 10;
        } 

        if(line.equals("DOWN")) {
          intensity -= 10;
        }

        ledcWrite(0, intensity);
      }

      delay(1);
    }

    client.stop();
  }
}
