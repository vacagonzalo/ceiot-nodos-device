#pragma once

#define LED 2
#define TIME 1000
#define BAUD_RATE 9600
#define RECONNECT_TIME 5000

#define SSID "Flia-Vaca"
#define PASSWORD "ragnarok"
#define PRONT_WIFI_CONNECTING "."
#define PRONT_WIFI_CONNECTED "device connected to "

#define MQTT_SERVER "192.168.0.9"
#define MQTT_PORT 1883
#define MQTT_USER "device"
#define MQTT_PASSWORD "thing"
#define CLIENT_ID "esp32"
#define DEVICE "esp32,"

#define PRONT_MQTT_CONNECTING "."
#define PRONT_MQTT_CONNECTED "device connected to "

#define DATA "data/temp"
#define CMND "cmnd/esp32"
#define RESET_ALL "reset/all"
#define RESET "reset/esp32"

#define MAX_TEMPERATURE 27
#define MIN_TEMPERATURE 12