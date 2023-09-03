
#include "WIFi_Wrapper.h"

WIFi_Wrapper::WIFi_Wrapper(const char *wifi_ssid, const char *password, WiFiClient *client) {
  _wifi_ssid = wifi_ssid;
  _password = password;
  _client = client;
}

WiFiClient* WIFi_Wrapper::GetClient(){
  return _client;
}

void WIFi_Wrapper::InitializeConnection() {
  WiFi.begin(_wifi_ssid, _password);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  
  Serial.println("Connected to Wi-Fi");
}

bool WIFi_Wrapper::IsConnected() {
  return WiFi.status() == WL_CONNECTED;
}

int WIFi_Wrapper::State() {
  return WiFi.status();
}
