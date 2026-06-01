//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include "sensors.h"

#include "data.h"

uint8_t getDeviceCount() {
    Serial.print("Locating devices...");
    uint8_t c = sensors.getDeviceCount();
    if (c == 0) {
        Serial.println("No devices found.");
        return -1;
    }
    Serial.println("Found " + String(c) + " devices.");
    return c;
}

String formatAddress(const DeviceAddress deviceAddress) {
    String s = "";
    constexpr uint8_t len = 8;

    for (uint8_t i = 0; i < len; i++) {
        if (i > 0) s += ",0x";
        else s += "0x";

        if (deviceAddress[i] < 16) s += "0";
        s += String(deviceAddress[i], HEX);
    }

    s.toUpperCase(); // Переводим все буквы в верхний регистр
    return s;
}

void printAddress(const DeviceAddress deviceAddress) {
    Serial.println(formatAddress(deviceAddress));
}

int8_t getTemperatureByDevice(Sensor s) {
    if (emulateTemp) {
        const int8_t t = getRandTemp();
        if (verbose) {
            Serial.printf("Random temperature for %s: %d°C\n", s.label, t);
        }
        return t;
    }

    const int16_t tempC = sensors.getTempC(s.address);
    if (verbose) {
        Serial.printf("Sensor %s (%s), temperature: %d°C\n", s.label, formatAddress(s.address).c_str(), tempC);
    }

    if (tempC == DEVICE_DISCONNECTED_C) {
        Serial.println("Error: Could not read temperature data");
        return tempC;
    }
    return tempC;
}

int8_t getRandTemp() {
    return random(0, 127);
}


IntercoolerTemp collectTemp() {
    IntercoolerTemp data;
    data.airIn = getTemperatureByDevice(airIn);
    data.airOut = getTemperatureByDevice(airOut);
    data.coolantIn = getTemperatureByDevice(coolantIn);
    data.coolantOut = getTemperatureByDevice(coolantOut);
    return data;
}


void showAllDevices() {
    if (sensorsCount > 0) {
        for (uint8_t i = 0; i < sensorsCount; i++) {
            DeviceAddress addr;
            if (sensors.getAddress(addr, i)) {
                Serial.printf("Address #%d: %s\n", i, formatAddress(addr).c_str());
            }
        }
    } else {
        Serial.println("No sensors found.");
    }
}
