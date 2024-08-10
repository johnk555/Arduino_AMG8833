#include <Wire.h>                     // It includes the necessary libraries: Wire.h for I2C communication and Adafruit_AMG88xx.h for interfacing with the AMG88xx sensor. 
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;             // It initializes an instance of the Adafruit_AMG88xx class called amg.

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {
    Serial.begin(9600);
    Serial.println(F("AMG88xx pixels"));

    bool status;

    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }

    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
}

//In the loop() function:
//It reads the temperature values of all pixels in the sensor array using amg.readPixels(pixels).
//It prints the temperature values of all pixels in the sensor array to the serial monitor.
//It delays for one second before repeating the process.

void loop() {
    //read all the pixels
    amg.readPixels(pixels);

    Serial.print("[");
    for(int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++){
        Serial.print(pixels[i]);
        Serial.print(", ");

    }

    Serial.println("]");
}
