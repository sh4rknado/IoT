#ifndef MQTT_Connector_h
#define MQTT_Connector_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "WIFi_Wrapper.h"

class MQTT_Connector {
    public:
        MQTT_Connector(IPAddress mqttServer, const char *mqttUser, const char *mqttPassword, PubSubClient *_cli, uint16_t mqttPort);
        bool IsConnected();
        void SetServer();
        bool Connect(String _mqttName);
        bool Publish(String _stateTopic, char buffer[256], size_t json);
        int State();

    private:
        IPAddress _mqttServer;
        uint16_t _mqttPort;
        const char *_mqttUser;
        const char *_mqttPassword;
        PubSubClient *_client;
};

#endif
