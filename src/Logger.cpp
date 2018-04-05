//
// Created by hector on 04/04/18.
//

#include "Logger.h"

Logger::Logger(HardwareSerial *serialDebug, int baudRate) {
    this->serialDebug = serialDebug;
}

void Logger::print(const char *msg) {
    if (serialDebug != nullptr) {
        serialDebug->print("[");
        serialDebug->print(debugName);
        serialDebug->print("]: ");
        serialDebug->print(msg);
        serialDebug->println("");
    }
}

void Logger::print(const String &msg) {
    print(msg.c_str());
}

const String &Logger::getDebugName() const {
    return debugName;
}

void Logger::setDebugName(const String &debugName) {
    Logger::debugName = debugName;
}


