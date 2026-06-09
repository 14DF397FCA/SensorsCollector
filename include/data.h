//
// Created by Gennadii Ilyashenko on 15.01.2026.
//

#ifndef SENSORSCOLLECTOR_DATA_H
#define SENSORSCOLLECTOR_DATA_H
#include <Arduino.h>

#include "DallasTemperature.h"

typedef struct IntercoolerTemp {
    int8_t airIn;
    int8_t airOut;
    int8_t coolantIn;
    int8_t coolantOut;
} IntercoolerTemp;

typedef struct Sensor {
    char label[32];
    DeviceAddress address;
} Sensor;

typedef struct LightSwitch {
    bool frontRight;
    bool frontLeft;
    bool headRight;
    bool headLeft;
    bool updated;
} LightSwitch;

extern const bool verbose;
extern const bool showAddresses;
extern LightSwitch lightSwitch;

#endif //SENSORSCOLLECTOR_DATA_H
