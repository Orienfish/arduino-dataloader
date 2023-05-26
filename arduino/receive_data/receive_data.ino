/*
  Multiple Serial test

  Receives from the main serial port, sends to the others.
  Receives from serial port 1, sends to the main serial (Serial 0).

  This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc.

  The circuit:
  - any serial device attached to Serial port 1 (for data transmission)
  - Serial Monitor open on Serial port 0 (for logging)

  created 30 Dec 2008
  modified 20 May 2012
  by Tom Igoe & Jed Roach
  modified 27 Nov 2015
  by Arturo Guadalupi

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/MultiSerialMega
*/

#include <SPI.h>
#include <SD.h>

File myFile;
char filename[] = "train_images.txt";

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.begin(9600);

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // Check to see if the file exists:
  if (SD.exists(filename)) {
    Serial.print(filename);
    Serial.println(" exists.");
    // delete the file:
    Serial.print("Removing ");
    Serial.print(filename);
    SD.remove(filename);
  } else {
    Serial.print(filename);
    Serial.println(" doesn't exist.");
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(filename, FILE_WRITE);
}

void loop() {
  // read from port 1, write to file:
  if (Serial1.available()) {
    byte inByte = Serial1.read(); 
    // Serial.write(inByte);
    if (inByte == byte('e')) {
      Serial.write(inByte);
      myFile.close();
    }
    else {
      myFile.write(inByte);
      Serial.write(inByte);
    }
  }
}
