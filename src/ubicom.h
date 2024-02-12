#ifndef UBICOM_H
#define UBICOM_H


#include <Arduino.h>
// // #include <NfcAdapter.h>
// // #include <PN532/PN532/PN532.h>
// // #include <SPI.h>
// // #include <Wire.h>
// // #include <PN532/PN532_SPI/PN532_SPI.h>
// // #include <PN532/PN532/PN532.h>
// // #include <NfcAdapter.h>

#include "PN532_HSU.h"
#include "PN532.h"
#include "NfcAdapter.h"
#include <Wire.h>
#include <SPI.h>
// #include "rgb_lcd.h"

// #include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>
#include "SoftwareSerial.h"


#include <PN532/PN532_HSU/PN532_HSU.h>
#include <ArduinoBLE.h>

#define LED 13

#define BLE_NAME "Arduino" // does not work properly if set to PalmLink 
#define SERVICE_UUID        "19b10000-e8f2-537e-4f6c-d104768a1214"
#define CHARACTERISTIC_UUID "19b10001-e8f2-537e-4f6c-d104768a1214"


PN532_HSU pn532hsu(Serial0); // Use the uart 0 of esp32 which corresponds to the pins RX,TX for arduino nano esp
NfcAdapter nfc(pn532hsu);

BLEService bleService(SERVICE_UUID); 
// BLEByteCharacteristic bleCharacteristic(CHARACTERISTIC_UUID, BLERead | BLEWrite | BLENotify);
BLECharacteristic bleCharacteristic(CHARACTERISTIC_UUID, BLERead | BLEWrite | BLENotify,"00000000");


uint8_t buffer[256];
uint8_t *pStr = NULL;
unsigned int n = 0;
uint16_t i = 0;


#endif