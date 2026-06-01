//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include <Arduino.h>
#include "OneWire.h"
#include "DallasTemperature.h"
#include "data.h"

#define ONE_WIRE_BUS 22
#define TEMPERATURE_PRECISION 9

extern OneWire oneWire;
extern DallasTemperature sensors;

extern Sensor airIn;
extern Sensor airOut;
extern Sensor coolantIn;
extern Sensor coolantOut;

extern uint8_t sensorsCount;
extern const bool emulateTemp;

#ifndef SENSORSCOLLECTOR_SENSORS_H
#define SENSORSCOLLECTOR_SENSORS_H

uint8_t getDeviceCount();

String formatAddress(const DeviceAddress deviceAddress);

void printAddress(DeviceAddress deviceAddress);

int8_t getTemperatureByDevice(Sensor s);

void printTemperature(DeviceAddress deviceAddress);

void printData(DeviceAddress deviceAddress);

int8_t getRandTemp();

IntercoolerTemp collectTemp();

void showAllDevices();

#endif //SENSORSCOLLECTOR_SENSORS_H
