//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include <Arduino.h>
#include "espnow.h"
#include "sensors.h"
#include "data.h"

const bool verbose = false;
const bool showAddresses = false;
//  Sensors
const bool emulateTemp = false;
constexpr bool sendData = true;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
uint8_t sensorsCount = 0;

Sensor airIn = {
    "airIn",
    {0x28, 0x61, 0x64, 0x35, 0xC6, 0x0B, 0xE0, 0x65}
};

Sensor airOut = {
    "airOut",
    {0x28, 0x61, 0x64, 0x35, 0xC6, 0x1E, 0x36, 0xFC}
};

Sensor coolantIn = {
    "coolantIn",
    {0x28, 0x61, 0x64, 0x35, 0xC6, 0x16, 0xA0, 0x46}
};

Sensor coolantOut = {
    "coolantOut",
    {0x28, 0x61, 0x64, 0x35, 0xC6, 0x24, 0xF3, 0xC3}
};

LightSwitch lightSwitch = {
    false,
    false,
    false,
    false,
    false
};

constexpr uint16_t updateInterval = 100;
static uint64_t lastUpdate = 0;

void ledSetup() {
    pinMode(14,OUTPUT);
    pinMode(26,OUTPUT);
    pinMode(33,OUTPUT);
    pinMode(32,OUTPUT);
}

void ledBlink() {
    if (verbose) {
        Serial.printf("f:l: %d\n", lightSwitch.frontLeft);
        Serial.printf("f:r: %d\n", lightSwitch.frontRight);
        Serial.printf("h:l: %d\n", lightSwitch.headLeft);
        Serial.printf("h:r: %d\n", lightSwitch.headRight);
        Serial.printf("upd: %d\n", lightSwitch.updated);
    }
    if (lightSwitch.updated) {
        digitalWrite(14, lightSwitch.frontLeft);
        digitalWrite(32, lightSwitch.frontRight);
        digitalWrite(33, lightSwitch.headLeft);
        digitalWrite(26, lightSwitch.headRight);
        lightSwitch.updated = false;
    }
}

void setup() {
    Serial.begin(115200);

    sensors.begin();
    sensors.setResolution(TEMPERATURE_PRECISION);
    sensorsCount = getDeviceCount();
    if (sensorsCount == 0) {
        Serial.println("Wait 10 seconds");
        ESP.restart();
    }

    showAllDevices();
    delay(1000);

    SetupEspNow();
    ledSetup();
}

void loop() {
    if (sensorsCount > 0) {
        if (millis() - lastUpdate > updateInterval) {
            sensors.requestTemperatures();

            ledBlink();

            if (sendData) {
                espSend(collectTemp());
            }

            if (showAddresses) {
                showAllDevices();
            }

            lastUpdate = millis();
        }
    } else {
        Serial.println("No sensors found");
    }
}
