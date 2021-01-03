#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define LED 2
#define TIME 1000
#define BAUD_RATE 9600
#define RECONNECT_TIME 5000

#define SSID "Flia-Vaca"
#define PASSWORD "ragnarok"

#define MQTT_SERVER "192.168.0.9"
#define MQTT_PORT 1883
#define MQTT_USER "device"
#define MQTT_PASSWORD "thing"
#define CLIENT_ID "esp32"

#define DATA "data/esp32/"
#define CMND "cmnd/esp32/"
#define RESET "cmnd/all"

void setup() {

}

void loop() {

}