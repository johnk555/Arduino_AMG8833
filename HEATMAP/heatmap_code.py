import serial
import time
from time import sleep
import numpy as np
import matplotlib.pyplot as plt
import re

# Function to read data from the serial port
def read_serial_data(ser):
    try:
        data = ser.readline().decode().strip()  # Read a line of data from the serial port
        return data
    except Exception as e:
        return None

# Function to parse the data received from the sensor
def parse_data(data):
    try:
        # Assuming the data is in CSV format (comma-separated values)
        values = [float(x) for x in data.split(',') if x.strip()]  # Filter out empty strings
        #print(values)
        return values
    except ValueError:
        #print(data)
        return None

def main():
    # Wait for AMG to boot
    sleep(0.1)

    # Prepare the heatmap
    fig, ax_lst = plt.subplots()
    dedomena = np.zeros((8, 8))
    heatmap = ax_lst.pcolor(dedomena, cmap=plt.cm.plasma)  # Colormaps here -> https://matplotlib.org/stable/gallery/color/colormap_reference.html
    fig.canvas.draw()
    plt.show(block=False)

    # Open the serial connection
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600)  # Replace 'COM1' with the correct serial port name for your sensor
    except Exception as e:
        print(f"Error opening serial connection: {e}")
        return

    # List to collect complete data lines
    collected_data = []

    # Loop to receive sensor values
    for i in range(500):
        # Read data from serial port

        data = read_serial_data(ser)
        print(data)

        with open('data.txt', 'w') as file:
           file.write(data)

        with open('data.txt', 'r') as file:
           txt = file.read().replace('[','\nSTART ').replace(']','\n').replace(',','').split('\n')

        print(txt)
        frames = 0
        for item in txt:
            if 'START' in item:
                tArray = np.fromstring(item.replace('START ',''), dtype=float, sep=' ')
                print ('max', np.max(tArray), 'avrg', round(np.mean(tArray),1))
                for i in range(0,8):
                    for j in range(0,8):
                        dedomena[i,j] = tArray[i*8+j];          # place new values on heatmap variable
        
                heatmap = ax_lst.pcolor(dedomena, cmap=plt.cm.plasma)
                fig.colorbar(heatmap, ax=ax_lst)  # Προσθέτει την κλίμακα
                ax_lst.draw_artist(ax_lst.patch)
                ax_lst.draw_artist(heatmap)
                fig.canvas.blit(ax_lst.bbox)
                fig.canvas.flush_events()                   # redraw heatmap
                time.sleep(0.05)                            # delay for playback reasons
                frames += 1                                 # simple frame counting

        #print("DONE, with number of frames: ", frames)   

    # Close the serial connection
    ser.close()


if __name__ == "__main__":
    main()
