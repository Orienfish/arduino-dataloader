import gzip
import numpy as np
import serial


############################################
# 1. Load dataset
############################################
def training_images():
    with gzip.open('MNIST/train-images-idx3-ubyte.gz', 'r') as f:
        # first 4 bytes is a magic number
        magic_number = int.from_bytes(f.read(4), 'big')
        # second 4 bytes is the number of images
        image_count = int.from_bytes(f.read(4), 'big')
        # third 4 bytes is the row count
        row_count = int.from_bytes(f.read(4), 'big')
        # fourth 4 bytes is the column count
        column_count = int.from_bytes(f.read(4), 'big')
        # rest is the image pixel data, each pixel is stored as an unsigned byte
        # pixel values are 0 to 255
        image_data = f.read()
        #images = np.frombuffer(image_data, dtype=np.uint8).reshape((image_count, -1))
        return image_data


def training_labels():
    with gzip.open('MNIST/train-labels-idx1-ubyte.gz', 'r') as f:
        # first 4 bytes is a magic number
        magic_number = int.from_bytes(f.read(4), 'big')
        # second 4 bytes is the number of labels
        label_count = int.from_bytes(f.read(4), 'big')
        # rest is the label data, each label is stored as unsigned byte
        # label values are 0 to 9
        label_data = f.read()
        #labels = np.frombuffer(label_data, dtype=np.uint8)
        return label_data

image_data = training_images()
label_data = training_labels()


############################################
# 2. Init serial port
############################################
# Note, baud rate on two ports must be the same
ser = serial.Serial('/dev/cu.usbserial-0001', 9600)
print('Init serial port {}'.format(ser.portstr))


############################################
# 3. Send training data over the port
############################################
# print(label_data)
#ser.write(b'adbdcd')
#ser.write(label_data)
ser.write(label_data[:10])
ser.write(b'eeeeeee')
ser.close()
