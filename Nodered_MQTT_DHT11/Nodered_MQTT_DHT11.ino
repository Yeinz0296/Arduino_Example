#include <simpleDHT.h>
#include <WiFi.h>
#include <MQTT.h>

#define WIFI_SSID             "Your_WiFi_Name"
#define WIFI_PASSWORD         "Your_WiFi_Password"
#define MQTT_HOST             "broker.hivemq.com"
#define MQTT_PREFIX_TOPIC     "Poli_Shah_Alam_0137594904/"
#define MQTT_PUBLISH_TOPIC    "/DHT11"
#define MQTT_SUBSCRIBE_TOPIC  "/LED"

WiFiClient net;
MQTTClient mqtt(1024);

int pinDHT11 = D5;
SimpleDHT11 dht11(pinDHT11);

unsigned long lastMillis = 0;

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi '" + String(WIFI_SSID) + "' ...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println(" connected!");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("Incoming Status: " + payload);
  Serial.println();
}

void connectToMqttBroker(){
  Serial.print("Connecting to '" + String(WIFI_SSID) + "' ...");
  
  mqtt.begin(MQTT_HOST, net);
  mqtt.onMessage(messageReceived);

  String uniqueString = String(WIFI_SSID) + "-" + String(random(1, 98)) + String(random(99, 999));
  char uniqueClientID[uniqueString.length() + 1];
  
  uniqueString.toCharArray(uniqueClientID, uniqueString.length() + 1);
  
  while (!mqtt.connect(uniqueClientID)) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");

  Serial.println("Subscribe to: " + String(MQTT_PREFIX_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC));
  
  mqtt.subscribe(String(MQTT_PREFIX_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC));

}

void setup() {
  
  Serial.begin(115200);
  delay(2000);
  Serial.println("\nMyduino IoT Kits & MQTT");
  connectToWiFi();
  connectToMqttBroker();

  Serial.println();

}

void loop() {
  mqtt.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  if (!mqtt.connected()) {
    connectToMqttBroker();
  }

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); 
    Serial.println(SimpleDHTErrDuration(err)); 
    delay(1000);
    return;
  }
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

    String dataInJson = "{";
    dataInJson += "\"temperature\":" + String(temperature) + ",";
    dataInJson += "\"humidity\":" + String(humidity) + ",";
    dataInJson += "}";

    Serial.println("Data to Publish: " + dataInJson);
    Serial.println("Length of Data: " + String(dataInJson.length()));
    Serial.println("Publish to: " + String(MQTT_PREFIX_TOPIC) + String(MQTT_PUBLISH_TOPIC));
    
    mqtt.publish(String(MQTT_PREFIX_TOPIC) + String(MQTT_PUBLISH_TOPIC), dataInJson);
  }

  Serial.println();

  delay(1500);
}
