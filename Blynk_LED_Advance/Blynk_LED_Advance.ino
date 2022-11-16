#include "fix.h"

BLYNK_WRITE(V0) {
  digitalWrite(D0, param.asInt());
}

void setup() {
  // put your setup code here, to run once:
  pinMode(D0, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
