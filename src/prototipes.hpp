#pragma once

#include <Arduino.h>

void configMQTT();
void connectWIFI();
void connectMQTT();
void on_message(char *topic, byte *payload, unsigned int length);
void attempt_to_reconnect();
boolean reconnect();
void send_data();
void subscribe_to_topics();