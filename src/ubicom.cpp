#include <Arduino.h>
#include "ubicom.h"


void setup(void) {
    SERIAL.begin(9600);
    SERIAL.println("NDEF Reader");
    nfc.begin();
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
        NdefMessage msg = tag.getNdefMessage();
        n = msg.getRecordCount();
        Serial.printf("======NFC TAG=======\n");
        for(i=0; i<n; i++){
            msg.getRecord(i).getPayload(buffer);
            int len = strlen((char*)buffer);
            Serial.printf("buff size %d\n", len);
            pStr = buffer + 3*sizeof(uint8_t); // points after the ".en" of the buffer
            Serial.printf("%s\n",pStr);
            bleCharacteristic.writeValue(pStr, len-3, false);
            bleCharacteristic.broadcast();
            memset(buffer,'\0', len); // reset the buffer with null char
        }
        Serial.printf("====================\n");
        digitalWrite(LED, LOW);
    }
    delay(1000);
}