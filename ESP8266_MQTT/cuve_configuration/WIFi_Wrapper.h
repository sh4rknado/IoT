#ifndef WIFi_Wrapper_h
#define WIFi_Wrapper_h

#include "Arduino.h"
#include <ESP8266WiFi.h>


class WIFi_Wrapper {
    public:
        WIFi_Wrapper(const char *wifi_ssid, const char *password, WiFiClient *client);
        void InitializeConnection();
        bool IsConnected();
        int State();
        WiFiClient* GetClient();

    private:
        const char *_password;
        const char *_wifi_ssid;
        WiFiClient *_client;
};

#endif
