#define BLYNK_TEMPLATE_ID "TMPL0jmW0yQ4"
#define BLYNK_DEVICE_NAME "MJII Training"
#define BLYNK_AUTH_TOKEN "ulAZtuiBWyWjM2lQBQDPokYzVigL5TbI"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleDHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "myinvententerprise";
char pass[] = "04222682";

int pinDHT11 = D1;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  byte temperature = 0;
  byte humidity = 0;
  //int err = SimpleDHTErrSuccess;
  dht11.read(&temperature, &humidity, NULL);
//  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
//    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
//    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
//    return;
//  }
    
  Blynk.virtualWrite(V0,temperature);
  Blynk.virtualWrite(V1,humidity);
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  delay(1500);
  
}
