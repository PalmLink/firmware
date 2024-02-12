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
// #define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
// #define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define SERVICE_UUID        "19b10000-e8f2-537e-4f6c-d104768a1214"
#define CHARACTERISTIC_UUID "19b10001-e8f2-537e-4f6c-d104768a1214"
// const char* SERVICE_UUID        "19b10000-e8f2-537e-4f6c-d104768a1214";
// const char* CHARACTERISTIC_UUID "19b10001-e8f2-537e-4f6c-d104768a1214";

// BLEServer *pServer = NULL;
// BLEService *pService = NULL;
// BLECharacteristic *pCharacteristic = NULL;


PN532_HSU pn532hsu(Serial0); // Use the uart 0 of esp32 which corresponds to the pins RX,TX for arduino nano esp
NfcAdapter nfc(pn532hsu);

BLEService bleService(SERVICE_UUID); 
// BLEByteCharacteristic bleCharacteristic(CHARACTERISTIC_UUID, BLERead | BLEWrite | BLENotify);
BLECharacteristic bleCharacteristic(CHARACTERISTIC_UUID, BLERead | BLEWrite | BLENotify,"00000000");


// rgb_lcd lcd;

// const int colorR = 255;
// const int colorG = 255;
// const int colorB = 255;

uint8_t buffer[256];
uint8_t *pStr = NULL;
unsigned int n = 0;
uint16_t i = 0;

// PINOUT for the lcd display: A4 white scl, A5 yellow

void setup(void) {
    // lcd.begin(16, 2);
    // lcd.printf("PalmLink startup...");
    SERIAL.begin(9600);
    SERIAL.println("NDEF Reader");
    nfc.begin();
    /**
     * BLE SETUP
    */
    // BLEDevice::init(BLE_NAME);
    // pServer = BLEDevice::createServer();
    // pService = pServer->createService(SERVICE_UUID);
    // pCharacteristic = pService->createCharacteristic(
    //                                      CHARACTERISTIC_UUID,
    //                                      BLECharacteristic::PROPERTY_READ |
    //                                      BLECharacteristic::PROPERTY_WRITE |
    //                                      BLECharacteristic::PROPERTY_NOTIFY
    //                                    );
    // // pCharacteristic->setValue(0);
    // pService->start();
    // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    // pAdvertising->addServiceUUID(SERVICE_UUID);
    // pAdvertising->setScanResponse(true);
    // // pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    // pAdvertising->setMinPreferred(0x12);
    // pAdvertising->start();

     if (!BLE.begin()) {
        Serial.println("- Starting BLE module failed!");
        while (1);
    }
    BLE.setLocalName(BLE_NAME);
    BLE.setAdvertisedService(bleService);
    bleService.addCharacteristic(bleCharacteristic);
    BLE.addService(bleService);
    // bleCharacteristic.writeValue(-1);
    BLE.advertise();
    // lcd.printf("Setup complete.");
    // lcd.setRGB(colorR, colorG, colorB);
    pinMode(LED, OUTPUT);
}

void loop(void) {
    SERIAL.println("\nReady to scan\n");
    BLEDevice central = BLE.central();
    BLE.advertise();
    if (nfc.tagPresent()) {
        digitalWrite(LED, HIGH);
        NfcTag tag = nfc.read();
        // tag.print();

        // lcd.clear();
        // lcd.setCursor(0,0);
        // lcd.printf("tag found\n");
        // delay(500);
        NdefMessage msg = tag.getNdefMessage();
        n = msg.getRecordCount();
        // Serial.printf("****%d****\n", n);
        // lcd.clear();
        // lcd.setCursor(0,0);
        Serial.printf("======NFC TAG=======\n");
        for(i=0; i<n; i++){
            msg.getRecord(i).getPayload(buffer);
            // Serial.printf("****%s*****\n",buffer);
            int len = strlen((char*)buffer);
            // lcd.printf("%s\n",buffer);
            Serial.printf("buff size %d\n", len);
            // pCharacteristic->setValue(buffer,len); // send value via BLE
            // pCharacteristic->notify();
            pStr = buffer + 3*sizeof(uint8_t); // points after the ".en" of the buffer
            Serial.printf("%s\n",pStr);
            // bleCharacteristic.writeValue(buffer[0]);
            // bleCharacteristic.setValue(pStr, len-3);
            
            bleCharacteristic.writeValue(pStr, len-3, false);
            bleCharacteristic.broadcast();
            memset(buffer,'\0', len); // reset the buffer with null char
            // Serial.println("buffer reset OK");
            // delay(500);
        }
        Serial.printf("====================\n");
        // delay(1000);
        digitalWrite(LED, LOW);
    }
    delay(1000);
}