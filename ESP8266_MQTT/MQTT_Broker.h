#ifndef MQTT_Broker_h
#define MQTT_Broker_h

#include "Arduino.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Dictionary.h"
#include "MQTT_Connector.h"

class MQTT_Broker {
    public:
        MQTT_Broker(int sensor_number, String unit_of_meas, String stateTopicPath, String dev_cla, String mqtt_name, MQTT_Connector *mqtt_connector);
        bool sendDiscovery(String discoveryTopic);
        bool sendPublish(dictionary kvp[]);
        void InitializeConnection();
        MQTT_Connector *MqttConnector;

    private:
        int _sensorNumber;     
        String _dev_cla;
        String _unit_of_meas;
        String _mqttName;
        String _stateTopic;
};

#endif
