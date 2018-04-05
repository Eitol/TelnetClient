//
// Created by hector on 04/04/18.
//

#ifndef TELNETCLIENT_TELNETCLIENT_H
#define TELNETCLIENT_TELNETCLIENT_H


#include <WString.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>
#include "Logger.h"

#define BUFFER_SIZE 128

struct TelnetConfig{
    String serverURL;
    uint16_t port;
    void (*onDataCallback)(String);
    void (*onDisconnectCallback)();
    HardwareSerial *serialDbg;
    int debugBaudRate;
    TelnetConfig(){
        debugBaudRate = 9600;
    }
};

class TelnetClient {
public:
    /**
     * @param serverURL i.e "192.168.3.129"
     * @param port i.e 6023
     */
    TelnetClient(TelnetConfig &telnetConfig);

    /** Connect to telnet server
     *
     * @return True on successful connection false otherwise
     */
    bool connect();

    /**
     * Wait for income data
     */
    void wait4Data();

private:
    void onStringComplete();
    void readAvailableData();
    void onDisconnect();

private:
    WiFiClient client;
    Logger *logger;
    bool stringComplete;
    String inputString;
    IPAddress serverIP;
    TelnetConfig cfg;
    char buffer[BUFFER_SIZE];

};


#endif //TELNETCLIENT_TELNETCLIENT_H
