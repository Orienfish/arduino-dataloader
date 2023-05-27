# arduino-dataloader

Setup a SD card, store the ML dataset in the SD card, and load the dataset on Arduino board.

### Getting Started

This quick setup takes Arduino Nano BLE 33 and MNIST dataset as an example.

* Connect the SD card reader with Arduino (using SPI). Format the SD card to FAT32.

* Download and unzip the MNIST dataset. Copy the prepared MNIST dataset (in `./laptop/MNIST`) to the SD card.

  Note, that due to the limitation on the filename length on the SD card, I rename the downloaded datasets:

  ```
  train-images-idx3-ubyte    -> tr-img // Training images
  train-labels-idx1-ubyte    -> tr-la  // Training labels
  t10k-images-idx3-ubyte     -> te-img // Testing images 
  t10k-labels-idx1-ubyte     -> te-la  // Testing labels
  	
  ```

* Use `load_data/load_data.ino` to load the dataset. Insert your code for training here.