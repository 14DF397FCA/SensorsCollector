//
// Created by Gennadii Ilyashenko on 15.01.2026.
//

#include <WiFi.h>
#include <esp_now.h>
#include "espnow.h"
#include "data.h"

// uint8_t broadcastAddress[] = {0xF8, 0xB3, 0xB7, 0x26, 0x1B, 0x60};
// uint8_t broadcastAddress[] = {0xAC, 0xA7, 0x04, 0xBD, 0xF6, 0x0C};
//  esp with 12864
// uint8_t broadcastAddress[] = {0x1C, 0xDB, 0xD4, 0x33, 0x7F, 0x20};
//  JC4827W543C
uint8_t broadcastAddress[] = {0x1C, 0xDB, 0xD4, 0x9B, 0x1C, 0xBC};


void SetupEspNow() {
    // Устанавливаем режим Wi-Fi
    WiFi.mode(WIFI_STA);

    //    Ждём поднятия WiFi
    uint32_t timeout = millis();
    while (WiFi.macAddress() == "00:00:00:00:00:00") {
        if (millis() - timeout > 3000) {
            Serial.println("WiFi init timeout!");
            break;
        }
        delay(10);
    }
    // Печатаем свой MAC-адрес
    Serial.print("Receiver MAC: ");
    Serial.println(WiFi.macAddress());

    // Инициализируем ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        delay(3000);
        ESP.restart();
    }

    // Регистрируем callback
    esp_now_register_send_cb(OnDataSent);

    // Добавляем broadcast peer
    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add broadcast peer");
        return;
    }

    Serial.println("Sender initialized. Ready to send...");
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Packet sent to: ");
    for (int i = 0; i < 6; i++) {
        Serial.print(mac_addr[i], HEX);
        if (i < 5) Serial.print(":");
    }
    Serial.printf(" at %d | Status: ", millis());
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success ✓" : "Fail ✗");
}

esp_err_t espSend(IntercoolerTemp data) {
    esp_err_t result = esp_now_send(broadcastAddress,
                                    (uint8_t *) &data,
                                    sizeof(data));

    return result;
}
