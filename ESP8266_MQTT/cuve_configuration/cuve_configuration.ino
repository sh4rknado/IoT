#include "WIFi_Wrapper.h"
#include "MQTT_Broker.h"

IPAddress mqttServer(192, 168, 1, 200);  // The IP of your MQTT broker
uint16_t mqttPort = 1883;
const char *mqttUser = "username";
const char *mqttPassword = "password";

// Numerical system for registering devices.
int sensorNumber = 1;
String unit_of_meas = "%";
String stateTopicPath = "home/cistern/";
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
  String discoveryTopic = "homeassistant/sensor/cistern_sensor_" + String(sensorNumber) + "/level/config";
  MQTTClient.sendDiscovery(discoveryTopic);
}

void loop() 
{
  int level=0;

  if (wifiWrapper.IsConnected()) {
    Serial.println("===== Sending Data =====");

    if (isnan(level)) {
       level = 0;
    }

    dictionary dico[1];
    dico[0] = {"level", String(level)};

    bool published = MQTTClient.sendPublish(dico);

    // Print the sensor values to Serial out (for debugging)
    Serial.println("published: ");
    Serial.println(published);
    Serial.println("level: ");
    Serial.println(level);    
  }
  else {
    Serial.println("WiFi Disconnected");
  }

  // Go into deep sleep mode for 60 seconds
  Serial.println("Deep sleep mode for 60 seconds");
  ESP.deepSleep(10e6);
}
