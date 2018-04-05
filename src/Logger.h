//
// Created by hector on 04/04/18.
//

#ifndef TELNETCLIENT_LOGGER_H
#define TELNETCLIENT_LOGGER_H


#include <HardwareSerial.h>

class Logger {
public:
    explicit Logger(HardwareSerial *serialDebug, int baudRate = 9600);

    void print(const char *msg);
    void print(const String &msg);
    const String &getDebugName() const;

    void setDebugName(const String &debugName);

private:
    HardwareSerial *serialDebug;
    String debugName;
};


#endif //TELNETCLIENT_LOGGER_H
