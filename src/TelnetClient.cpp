//
// Created by hector on 04/04/18.
//

#include "TelnetClient.h"

TelnetClient::TelnetClient(TelnetConfig &telnetConfig) :
        cfg(telnetConfig), stringComplete(false) {
    logger = new Logger(cfg.serialDbg, cfg.debugBaudRate);
    stringComplete = false;
    logger->setDebugName("NODE");
    if (!this->serverIP.fromString(cfg.serverURL)) {
        logger->print("Invalid IP!. Must be like \"192.168.3.129\"");
    }
}

bool TelnetClient::connect() {
    logger->print("connecting...");
    // if you get a connection, report back via serial:
    if (client.connect(serverIP, cfg.port)) { //port to connect to; telnet/TCP
        logger->print("connected");
        return true;
    } else {
        logger->print("connection failed");
        return false;
    }
}

void TelnetClient::wait4Data() {
    if (stringComplete) {
        onStringComplete();
    }

    if (client.available()) {
        readAvailableData();
    }
    if (!client.connected()) {
        onDisconnect();
    }
}


void TelnetClient::onStringComplete(){
    logger->print("Received:");
    logger->print(inputString);
    String newData = inputString;
    inputString = "";
    stringComplete = false;
    if (cfg.onDataCallback != nullptr) {
        cfg.onDataCallback(newData);
    }
}

void TelnetClient::readAvailableData(){
    // TODO: Optimize using readBytesUntil
    auto c = char(client.read());
    inputString += c;
    if (c == '\n') {
        stringComplete = true;
    }
}

void TelnetClient::onDisconnect(){
    logger->print("Disconnecting.");
    if (cfg.onDisconnectCallback != nullptr) {
        cfg.onDisconnectCallback();
    }
    client.stop();
}
