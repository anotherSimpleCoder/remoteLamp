#include <Arduino.h>
#include <WiFi.h>

#define UP_BUTTON 3
#define DOWN_BUTTON 7
#define STATUS_LED 6

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
  pinMode(STATUS_LED, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin("LAMP", "1234567890");

  while(WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  if(client.connect("192.168.4.1", 80)) {
    digitalWrite(STATUS_LED, HIGH);
  }
}

void loop() {
  if(client.connected()) {
    client.println("Hello world!");

    bool up_button_pressed = digitalRead(UP_BUTTON);
    bool down_button_pressed = digitalRead(DOWN_BUTTON);

    if(up_button_pressed) {
      client.println("UP");
    }

    if(down_button_pressed) {
      client.println("DOWN");
    }

  } else {
    digitalWrite(STATUS_LED, LOW);
    client.connect("192.168.1.0", 80);
    digitalWrite(STATUS_LED, HIGH);
  }

  delay(100);
}
