#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

int value = 0;
float voltage;
const char *ssid = "MyFios";
const char *password = "fURl62exIT54ice";

WiFiUDP udp;
IPAddress target(192,168,1,168);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(74880);
  pinMode(D0, INPUT_PULLDOWN_16);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  
  value = analogRead(D0);
  voltage = value * 3.3 / 1023;
  delay(1000);
  bool open = false;
  if (voltage > 1.5){
    open = true;
  }
  else{
    open = false;
  }
  udp.beginPacket(target, 4021);
  udp.write(open);
  udp.endPacket();
}
