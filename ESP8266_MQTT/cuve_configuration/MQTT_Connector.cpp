
#include "MQTT_Connector.h"

MQTT_Connector::MQTT_Connector(IPAddress mqttServer, const char *mqttUser, const char *mqttPassword, PubSubClient *_cli, uint16_t mqttPort) {
  _mqttServer = mqttServer;
  _mqttUser = mqttUser;
  _mqttPassword = mqttPassword;
  _mqttPort = mqttPort;
  _client = _cli;
}

bool MQTT_Connector::IsConnected() {
  return _client->connected();
}

void MQTT_Connector::SetServer() {
  _client->setServer(_mqttServer, _mqttPort);
}

bool MQTT_Connector::Connect(String _mqttName) {
  return _client->connect(_mqttName.c_str(), _mqttUser, _mqttPassword);
}

bool MQTT_Connector::Publish(String _stateTopic, char buffer[256], size_t json) {
  return _client->publish(_stateTopic.c_str(), buffer, json);
}

int MQTT_Connector::State() {
  return _client->state();
}