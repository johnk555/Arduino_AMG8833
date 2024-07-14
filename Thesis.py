import serial
import time
from time import sleep
import numpy as np

# Function to read data from the serial port
def read_serial_data(ser):
    data = ser.readline().decode().strip()  # Read a line of data from the serial port
    return data

# Function to parse the data received from the sensor
def parse_data(data):
    try:
        # Assuming the data is in CSV format (comma-separated values)
        values = [float(x) for x in data.split(',') if x.strip()]  # Filter out empty strings
        print(data)

        return values
    except ValueError:
        print(data)
        return None


def main():
    # wait for AMG to boot
    sleep(0.1)

    # Άνοιγμα σύνδεσης με το σειριακό πόρτα
    global ser
    ser = serial.Serial('COM6',
                        9600)  # Αντικαταστήστε 'COM1' με το όνομα του σειριακού πόρτα που χρησιμοποιεί ο αισθητήρας

    # Λίστα για την αποθήκευση των τιμών αισθητήρα
    sensor_values = []

    # Επανάληψη για λήψη των τιμών του αισθητήρα
    for _ in range(500):
        # Διάβασμα δεδομένων από το σειριακό πόρτα
        # Read data from serial port
        data = read_serial_data(ser)

        # Parse the data
        values = parse_data(data)

    # Κλείσιμο σύνδεσης με το σειριακό πόρτα
    ser.close()

    # Υπολογισμός αθροίσματος και μέσου όρου
    total = sum(data)
    average = total / len(data)

    # Calculate the minimum and maximum values along with their positions
    min_value = np.min(data)
    max_value = np.max(data)
    min_position = np.where(data == min_value)
    max_position = np.where(data == max_value)

    # Print the results
    print("Minimum value:", min_value, "at position:", min_position)
    print("Maximum value:", max_value, "at position:", max_position)

    # Εκτύπωση αποτελεσμάτων
    print("Σύνολο:", total)
    print("Μέσος όρος:", average)


if __name__ == "__main__":
    main()
