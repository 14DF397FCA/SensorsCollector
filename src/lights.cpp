//
// Created by Gennadii Ilyashenko on 09.06.2026.
//

#include <Arduino.h>
#include "lights.h"

void setupLights() {
    pinMode(14,OUTPUT);
    pinMode(26,OUTPUT);
    pinMode(33,OUTPUT);
    pinMode(32,OUTPUT);
}

void turnLights() {
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
