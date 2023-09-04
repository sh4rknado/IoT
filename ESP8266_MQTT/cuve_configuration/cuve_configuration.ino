#include "WIFi_Wrapper.h"
#include "MQTT_Broker.h"

IPAddress mqttServer(192, 168, 1, 178);  // The IP of your MQTT broker
uint16_t mqttPort = 1883;
const char *mqttUser = "homeassistant";
const char *mqttPassword = "chi7zaisuTh1ohgaiqu1ahfahseelooYohxoo5Dahzi2oQuaecook0Thah2oPh4l";

// Numerical system for registering devices.
int sensorNumber = 1;
String unit_of_meas = "%";
String stateTopicPath = "home/cuve/state";
String dev_cla = "level";
String mqttName = "Rainwater Cistern";

/* Define object */
WiFiClient wifi; // WiFi Client
PubSubClient client(wifi); //MQTT Client
WIFi_Wrapper wifiWrapper("WiFi-2.4-DC03", "AC4635D555", &wifi);
MQTT_Connector MQTTConnector(mqttServer, mqttUser, mqttPassword, &client, mqttPort);
MQTT_Broker MQTTClient(sensorNumber, unit_of_meas, stateTopicPath, dev_cla, mqttName, &MQTTConnector);

void setup() {
  Serial.begin(115200); // enable debug
  delay(100); // wait debug initialize

  // initialize all connections  
  wifiWrapper.InitializeConnection();
  MQTTClient.InitializeConnection();
  
  // Send MQTT Discovery Requesr
  // String discoveryTopic = "homeassistant/binary_sensor/cuve_sensor_" + String(sensorNumber) + "/config";
  // MQTTClient.sendDiscovery(discoveryTopic);
}

void loop() 
{
  int level=0;

  if (wifiWrapper.IsConnected()) {
    Serial.println("===== Sending Data =====");

    if (isnan(level)) {
       level = 10;
    }

    bool published = MQTTClient.sendPublish(level);

    // Print the sensor values to Serial out (for debugging)
    Serial.println("published: " + String(published));
    Serial.println("level: " + String(level));
  }
  else {
    Serial.println("WiFi Disconnected");
  }

  // Go into deep sleep mode for 60 seconds
  Serial.println("Deep sleep mode for 60 seconds");
  ESP.deepSleep(6e7); 
}
