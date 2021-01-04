#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h> // PubSubClient by Nick O'Leary
                          // https://github.com/knolleary/pubsubclient

#include "./definitions.hpp"
#include "./prototipes.hpp"

WiFiClient wifi;
PubSubClient mqtt;

long lastReconnectAttemp{0};
int frec{TIME};
int direction{0};
void setup()
{
  Serial.begin(BAUD_RATE);
  configMQTT();
  connectWIFI();
  connectMQTT();
  subscribe_to_topics();
}

void loop()
{
  if (!mqtt.connected())
  {
    attempt_to_reconnect();
  }
  else
  {
    mqtt.loop();
    send_data();
  }
}

void on_message(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, "cmnd/esp32/frec"))
  {
    Serial.println("frec");
  }
  else if (strcmp(topic, "cmnd/reset-all"))
  {
    Serial.println("reset-all");
    direction = 0;
  }
  else if (strcmp(topic, "cmnd/esp32/reset"))
  {
    Serial.println("reset");
    direction = 0;
  }
  else if (strcmp(topic, "cmnd/esp32/calibrate"))
  {
    Serial.println("calibrate");
    direction = 1;
  }
  else
  {
    Serial.println(topic);
  }

  Serial.print(": ");
  for (unsigned int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void send_data()
{
  String temperature = String(random(MIN_TEMPERATURE, MAX_TEMPERATURE));
  String my_message = String(DEVICE + temperature);
  if (direction == 0)
  {
    mqtt.publish(DATA, my_message.c_str());
  }
  else
  {
    mqtt.publish(LIVE, my_message.c_str());
  }

  delay(frec);
}

////////////////////////////////////////////////////////////////////////////////

void configMQTT()
{
  mqtt.setClient(wifi);
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(on_message);
}

void connectWIFI()
{
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(TIME);
    Serial.print(PRONT_WIFI_CONNECTING);
  }
  Serial.print(PRONT_WIFI_CONNECTED);
  Serial.println(SSID);
}

void connectMQTT()
{
  while (!mqtt.connect(CLIENT_ID, MQTT_USER, MQTT_PASSWORD))
  {
    delay(TIME);
    Serial.print(PRONT_MQTT_CONNECTING);
  }
  Serial.print(PRONT_MQTT_CONNECTED);
  Serial.println(MQTT_SERVER);
}

void attempt_to_reconnect()
{
  long now = millis();
  if (now - lastReconnectAttemp > RECONNECT_TIME)
  {
    lastReconnectAttemp = now;
    if (reconnect())
    {
      lastReconnectAttemp = 0;
    }
  }
}

boolean reconnect()
{
  if (mqtt.connect(CLIENT_ID, MQTT_USER, MQTT_PASSWORD))
  {
    subscribe_to_topics();
  }
  return mqtt.connected();
}

void subscribe_to_topics()
{
  mqtt.subscribe(CMND);
  mqtt.subscribe(RESET);
  mqtt.subscribe(RESET_ALL);
}