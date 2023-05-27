/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/


#include <SPI.h>
#include <SD.h>

#define IMAGE_SIZE 784

char train_images[] = "tr-img";
char train_labels[] = "tr-la";
char test_images[] = "te-img";
char test_labels[] = "te-la";
File train_image_file, train_label_file;
File test_image_file, test_label_file;

// Byte is a data type of 8-bit integers, 0-255
byte data;
byte image[IMAGE_SIZE];
byte label;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file for reading:
  train_image_file = SD.open(train_images);
  train_label_file = SD.open(train_labels);
  // test_image_file = SD.open(test_images);
  // test_label_file = SD.open(test_labels);
  int i;
  if (train_image_file && train_label_file) {
    // read from the training dataset
    while (train_image_file.available() && 
      train_label_file.available()) {
      // read one image sample
      for (i = 0; i < IMAGE_SIZE; ++i) {
        data = train_image_file.read();
        image[i] = data;
      }

      // read one label sample
      label = train_label_file.read();

      // Insert your code for training here
      // Currrently I just print out the training sample: image and label
      for (i = 0; i < IMAGE_SIZE; ++i) {
        Serial.print(image[i]);
        Serial.print(" ");
      }
      Serial.println("");
      Serial.println(label);
    }

    // close the file:
    train_image_file.close();
    train_label_file.close();
  } else {
    // if the file didn't open, print an error:
    Serial.print("error opening ");
    Serial.println(train_images);
  }
}

void loop() {
  // nothing happens after setup
}


