This firmware is inspired from: https://github.com/marianylund/BleWinrtDll

# Install the environnment and compile the firmware:

- install the platform.io extension on VSCode
- clone the firmware repo
- download the lib https://github.com/Seeed-Studio/PN532/ and extract the folders "PN532" and "PN532_HSU" into .pio/libdeps/
- click on "build"
- double click on the arduino until the led blinks green
- click on "upload" to upload firmware on the arduino card  

# The firmware

This firmware reads the content of NFC tags (stored as text values), and put the value into a characteristic of the GATT server. The Hololens can then act as a BLE client and read the value on the characteristic periodically.

When a tag is read, the internal led of the arduino nano esp32 board will glow shortly. 

# Known bugs

Sometimes, if the tag is removed from the reader while the scanner is reader, there can be an error. When this happens, the led will stay on. In this case, the arduino might need to be reset.