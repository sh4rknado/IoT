
#include "MQTT_Broker.h"

MQTT_Broker::MQTT_Broker(int sensor_number, String unit_of_meas, String stateTopicPath, String dev_cla, String mqtt_name, MQTT_Connector *mqtt_connector) {
  _sensorNumber = sensor_number;
  _unit_of_meas = unit_of_meas;
  _stateTopic = stateTopicPath + String(_sensorNumber) + "/state";
  _dev_cla = dev_cla;
  _mqttName = mqtt_name + " " + String(_sensorNumber);
  MqttConnector = mqtt_connector;
}

void MQTT_Broker::InitializeConnection() {
  MqttConnector->SetServer();
  Serial.println("Connecting to MQTT");

  while(!MqttConnector->IsConnected()){
    Serial.print(".");
    delay(2000);

    if (MqttConnector->Connect(_mqttName)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.println("failed with state ");
      // Serial.print(MqttConnector->Client.state());
      delay(2000);
    }
  }
}

bool MQTT_Broker::sendDiscovery(String discoveryTopic) {
    DynamicJsonDocument doc(1024);
    char buffer[256];

    doc["name"] = _mqttName;
    doc["stat_t"]   = _stateTopic;
    doc["unit_of_meas"] = _unit_of_meas;
    doc["dev_cla"] = _dev_cla;
    doc["frc_upd"] = true;
    doc["val_tpl"] = "{{ value_json." + _dev_cla + "|default(0) }}";

    size_t n = serializeJson(doc, buffer);
    return MqttConnector->Publish(discoveryTopic, buffer, n);
}

bool MQTT_Broker::sendPublish(dictionary kvp[]) {
    DynamicJsonDocument doc(1024);
    char buffer[256];

    for(int i=0; i < sizeof(kvp); i++) {
      doc[kvp[i].key] = kvp[i].value; 
    }

    size_t n = serializeJson(doc, buffer);
    return MqttConnector->Publish(_stateTopic, buffer, n);
}
