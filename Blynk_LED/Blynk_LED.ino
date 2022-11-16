#define BLYNK_TEMPLATE_ID           "TMPLhG6gPbsB"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "wUTTLYxbzMH4jd2W7afFw9T1Qh9k6Cfq"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "myinvententerprise";
char pass[] = "04222682";

BLYNK_WRITE(V0) {
  digitalWrite(D1, param.asInt());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
