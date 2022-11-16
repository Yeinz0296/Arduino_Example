#define BLYNK_TEMPLATE_ID "TMPL0jmW0yQ4"
#define BLYNK_DEVICE_NAME "MJII Training"
#define BLYNK_AUTH_TOKEN "ulAZtuiBWyWjM2lQBQDPokYzVigL5TbI"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "myinvententerprise";
char pass[] = "04222682";

WidgetLCD lcd(V2);

void setup() {
  Serial.begin(9600);
  pinMode(D1, INPUT);
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
  lcd.print(4,0,"Hello");
}

void loop() {
  Blynk.run();
  lcd.print(4,1,digitalRead(D1));
//  Blynk.virtualWrite(V0, "Hello");
//  if ( digitalRead(D1) == HIGH){
//    Blynk.virtualWrite(V1, "Button On");
//  }
//  else{
//    Blynk.virtualWrite(V1, "Button Off");
//  }
//  Serial.print(digitalRead(D1));
//  delay(10); 
}
