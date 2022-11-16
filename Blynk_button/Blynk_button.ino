#define BLYNK_TEMPLATE_ID "TMPL0jmW0yQ4"
#define BLYNK_DEVICE_NAME "MJII Training"
#define BLYNK_AUTH_TOKEN "ulAZtuiBWyWjM2lQBQDPokYzVigL5TbI"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "myinvententerprise";
char pass[] = "04222682";

void setup() {
  Serial.begin(9600);
  pinMode(D1, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  Blynk.virtualWrite(V0, digitalRead(D1));
  Serial.print(digitalRead(D1)); 
}
