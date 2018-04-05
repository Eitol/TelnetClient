#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>
#include "src/TelnetClient.h"

void onDataCallBack(String data) {
    Serial.print("DATA: ");
    Serial.print(data);
}


TelnetConfig createTelnetConfig() {
    TelnetConfig cfg;
    cfg.serverURL = "192.168.3.129";
    cfg.port = 6023;
    cfg.serialDbg = &Serial;
    cfg.onDataCallback = &onDataCallBack;
    return cfg;
}

TelnetConfig cfg = createTelnetConfig();
TelnetClient client(cfg);

void setup() {
    Serial.begin(9600);
    ESP8266WiFiMulti WiFiMulti;
    WiFiMulti.addAP("TEST_ESP8266", "test2018");
    while (WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }
    cfg.serialDbg->println("WiFi connected. IP address: ");
    cfg.serialDbg->println(WiFi.localIP());
    delay(50);
    if (!client.connect()) {
        cfg.serialDbg->print(":(");
    }
}

void loop() {
    client.wait4Data();
}

